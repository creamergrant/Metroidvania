// Fill out your copyright notice in the Description page of Project Settings.


#include "MMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "UObject/ConstructorHelpers.h"
#include "InputActionValue.h"
#include "MOneWayPlatform.h"
#include "MCharacter.h"
#include "MDoubleJumpComponent.h"

UMMovementComponent::UMMovementComponent()
{
	m_movementValue = { 0.0f, 0.0f };
	m_movementSpeed = 1000.0f;

	m_maxJumpHeight = 1.0f;
	m_jumpTimeMax = 0.0f;
	m_jumpTimeCurrent = 0.0f;
	m_bIsJumping = false;
	m_bIsAirborne = false;
	m_bDoSweep = true;
	m_coyoteTimeAmount = 0.01f; //experiment with this
	m_sweepStartOffset = 0.0f;
	m_sweepDistance = 100.0f;

	//locks movement to X/Y plane
	bConstrainToPlane = true;
	PlaneConstraintNormal = GetPlaneConstraintNormalFromAxisSetting(EPlaneConstraintAxisSetting::Y);

	static ConstructorHelpers::FObjectFinder<UCurveFloat> Curve(TEXT("/Game/Blueprint/TestCurve"));
	if (Curve.Object != NULL)
	{
		m_jumpCurve = Curve.Object;
	}
}

void UMMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	UBoxComponent* Box = Cast<UBoxComponent>(UpdatedPrimitive);
	if (Box)
	{
		FVector HalfExtent = Box->GetScaledBoxExtent();
		FVector3f RealHalfExtent = { (float)HalfExtent.X, (float)HalfExtent.Y, (float)HalfExtent.Z };
		m_sweepShape.SetBox(RealHalfExtent);
	}

	m_sweepQueryParams.AddIgnoredComponent(UpdatedPrimitive);
	m_sweepQueryParams.AddIgnoredActor(GetOwner());

	if (m_jumpCurve)
	{
		float temp;
		m_jumpCurve->GetTimeRange(temp, m_jumpTimeMax);
	}
	m_character = Cast<AMCharacter>(UpdatedComponent->GetOwner());
}

void UMMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UWorld* World = GetWorld();
	if (World && m_bDoSweep)
	{
		FHitResult Hit;
		FVector RayStart = UpdatedComponent->GetComponentLocation() + (-UpdatedComponent->GetUpVector() * m_sweepStartOffset);
		FVector RayEnd = RayStart + (-UpdatedComponent->GetUpVector() * m_sweepDistance);

		bool bFoundHit = World->SweepTestByChannel(RayStart, RayEnd, UpdatedPrimitive->GetComponentQuat(), ECollisionChannel::ECC_WorldStatic, m_sweepShape, m_sweepQueryParams);

		if (!bFoundHit && !World->GetTimerManager().IsTimerActive(m_coyoteTimeTimer) && !m_bIsAirborne)
		{
			World->GetTimerManager().SetTimer(m_coyoteTimeTimer, this, &UMMovementComponent::EndCoyoteTime, m_coyoteTimeAmount, false);
			m_bIsAirborne = true;
		}
		else if (bFoundHit)
		{
			World->GetTimerManager().ClearTimer(m_coyoteTimeTimer);
			m_bIsAirborne = false;
			m_bCanJump = true;
		}
	}

	if (m_bIsJumping)
	{
		CheckAbove();
	}
	if (!m_bIsJumping && m_bIsAirborne)
	{
		CheckBellow();
	}

	if (!FMath::IsNearlyZero(m_movementValue.X))
	{
		FVector Delta = { -m_movementValue.X * m_movementSpeed * DeltaTime, 0.0f, 0.0000001f };
		MoveUpdatedComponent(Delta, UpdatedPrimitive->GetComponentRotation(), true);
	}
	GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Red, FString::SanitizeFloat(m_movementValue.Y));

	if (m_bIsJumping && m_jumpTimeCurrent < m_jumpTimeMax)
	{
		float JumpHeightMultiplier = m_jumpCurve->GetFloatValue(m_jumpTimeCurrent); //get multiplier at current time

		FHitResult Hit;

		FVector Delta = { 0, 0, m_maxJumpHeight * JumpHeightMultiplier };
		MoveUpdatedComponent(Delta, UpdatedPrimitive->GetComponentRotation(), true, &Hit, ETeleportType::None);

		m_jumpTimeCurrent += DeltaTime;

		//checks the dot product of the collision normal against the up vector, if they are close enough to each other, youve hit your head and should stop jumping.
		if (Hit.ImpactNormal.Dot(FVector::UpVector) < -0.51f)
		{
			m_bIsJumping = false;
			m_jumpTimeCurrent = m_jumpTimeMax + 1.0f; //sets condition to prevent perma jump held bouncing
			//UpdatedPrimitive->SetEnableGravity(true);
		}
	}
	else if (m_bIsJumping && m_jumpTimeCurrent >= m_jumpTimeMax)
	{
		m_bIsJumping = false;
		m_jumpTimeCurrent = m_jumpTimeMax + 1.0f; //sets condition to prevent perma jump held bouncing
		//UpdatedPrimitive->SetEnableGravity(true);
	}
}

void UMMovementComponent::Move(const FVector2D& Value)
{
	m_movementValue = Value;
}

void UMMovementComponent::Jump()
{
	if (m_movementValue.Y == -1)
	{
		DropDown();
		return;
	}
	if (m_bCanJump && !m_bIsJumping && m_jumpTimeCurrent < m_jumpTimeMax) //last condition is to prevent perma bounce if jump is held
	{
		m_bIsAirborne = true;
		m_bIsJumping = true;
		m_bDoSweep = false; //temporary coyote time lockout to prevent quick tap double jumps
		m_bCanJump = false;

		//enables coyote time shortly after a single frame (assuming 60 fps)
		FTimerHandle SweepEnable;
		GetWorld()->GetTimerManager().SetTimer(SweepEnable, this, &UMMovementComponent::EnableSweepCheck, 0.017f, false);

		//UpdatedPrimitive->SetEnableGravity(false);
	}
}

void UMMovementComponent::JumpEnd()
{
	m_bIsJumping = false;
	m_jumpTimeCurrent = 0.0f;
	//UpdatedPrimitive->SetEnableGravity(true);

	if (AMCharacter::ContainsClassType<UMDoubleJumpComponent>(m_character->m_movementComps) && m_bIsAirborne)
	{
		m_bCanJump = true;
	}
}

void UMMovementComponent::EnableSweepCheck()
{
	m_bDoSweep = true;
}

void UMMovementComponent::EndCoyoteTime()
{
	m_bCanJump = false;
}

void UMMovementComponent::CheckAbove()
{
	UWorld* world = GetWorld();
	if (!world) return;
	TArray<FHitResult> hits;
	FVector start = UpdatedComponent->GetComponentLocation() + (UpdatedComponent->GetUpVector() * 100);
	FVector end = UpdatedComponent->GetUpVector() * 1 + start;

	FCollisionShape shape = FCollisionShape::MakeBox(FVector(80, 50, 50));

	DrawDebugLine(world, start, end, FColor::Red);
	DrawDebugBox(GetWorld(), end, FVector(80, 50, 50), FColor::Red);

	world->SweepMultiByChannel(hits, start, end, shape.GetBox().Rotation().Quaternion(), ECC_WorldDynamic, shape, m_sweepQueryParams);
	
	for (int i = 0; i < hits.Num(); i++)
	{
		if (AMOneWayPlatform* plat = Cast<AMOneWayPlatform>(hits[i].GetActor()))
		{
			plat->m_hitBox->SetCollisionProfileName("OneWay");
		}
		else
		{
			
		}
	}
}

void UMMovementComponent::CheckBellow()
{
	UWorld* world = GetWorld();
	if (!world) return;
	TArray<FHitResult> hits;
	FVector start = UpdatedComponent->GetComponentLocation() + (-UpdatedComponent->GetUpVector() * 100);
	FVector end = -UpdatedComponent->GetUpVector() * 1 + start;

	FCollisionShape shape = FCollisionShape::MakeBox(FVector(80, 10, 10));

	DrawDebugLine(world, start, end, FColor::Red);
	DrawDebugBox(GetWorld(), end, FVector(80, 10, 10), FColor::Red);

	world->SweepMultiByChannel(hits, start, end, shape.GetBox().Rotation().Quaternion(), ECC_WorldDynamic, shape, m_sweepQueryParams);

	for (int i = 0; i < hits.Num(); i++)
	{
		if (AMOneWayPlatform* plat = Cast<AMOneWayPlatform>(hits[i].GetActor()))
		{
			plat->m_hitBox->SetCollisionProfileName("BlockAll");
		}
		else
		{

		}
	}
}

void UMMovementComponent::DropDown()
{
	UWorld* world = GetWorld();
	if (!world) return;
	TArray<FHitResult> hits;
	FVector start = UpdatedComponent->GetComponentLocation() + (-UpdatedComponent->GetUpVector() * 100);
	FVector end = -UpdatedComponent->GetUpVector() * 1 + start;

	FCollisionShape shape = FCollisionShape::MakeBox(FVector(80, 10, 10));

	DrawDebugLine(world, start, end, FColor::Red);
	DrawDebugBox(GetWorld(), end, FVector(80, 10, 10), FColor::Red);

	world->SweepMultiByChannel(hits, start, end, shape.GetBox().Rotation().Quaternion(), ECC_WorldDynamic, shape, m_sweepQueryParams);

	for (int i = 0; i < hits.Num(); i++)
	{
		if (AMOneWayPlatform* plat = Cast<AMOneWayPlatform>(hits[i].GetActor()))
		{
			plat->m_hitBox->SetCollisionProfileName("OneWay");
		}
		else
		{

		}
	}
}

