// Fill out your copyright notice in the Description page of Project Settings.


#include "MMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/TimelineComponent.h"
#include "Curves/CurveFloat.h"
#include "UObject/ConstructorHelpers.h"
#include "InputActionValue.h"
#include "MOneWayPlatform.h"

UMMovementComponent::UMMovementComponent()
{
	m_movementValue = { 0.0f, 0.0f };
	m_movementSpeed = 500.0f;

	m_maxJumpHeight = 100.0f;
	m_startJumpHeight = 0.0f;
	m_jumpTimeMax = 0.0f;
	m_jumpTimeCurrent = 0.0f;
	m_bIsJumping = false;
	m_bIsAirborne = false;
	m_bDoSweep = true;
	m_coyoteTimeAmount = 0.25f;
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
	//check(Box != nullptr); //pseudo if statement that lets me know that i can use updated primitive freely without needing to if check it all the time.
	if (Box)
	{
		FVector HalfExtent = Box->GetScaledBoxExtent();
		FVector3f RealHalfExtent = { (float)HalfExtent.X, (float)HalfExtent.Y, (float)HalfExtent.Z };
		m_sweepShape.SetBox(RealHalfExtent);
	}
	
	m_sweepQueryParams.AddIgnoredComponent(UpdatedPrimitive);

	if (m_jumpCurve)
	{
		float temp;
		m_jumpCurve->GetTimeRange(temp, m_jumpTimeMax);
	}
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
		}
		else if (bFoundHit)
		{
			World->GetTimerManager().ClearTimer(m_coyoteTimeTimer);
			m_bIsAirborne = false;
		}
	}

	if (m_bIsAirborne)
	{
		CheckAbove();
	}
	if (!m_bIsJumping && m_bIsAirborne)
	{
		CheckBelow();
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

		if (Hit.ImpactNormal.Dot(FVector::UpVector) < -0.5f)
		{
			m_bIsJumping = false;
		}
	}
	else if (m_bIsJumping && m_jumpTimeCurrent >= m_jumpTimeMax)
	{
		m_bIsJumping = false;
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
	if (!m_bIsAirborne && !m_bIsJumping)
	{
		m_bIsAirborne = true;
		m_bIsJumping = true;
		m_bDoSweep = false;
		m_jumpTimeCurrent = 0.0f;

		m_startJumpHeight = UpdatedPrimitive->GetComponentLocation().Z;

		FTimerHandle SweepEnable;
		GetWorld()->GetTimerManager().SetTimer(SweepEnable, this, &UMMovementComponent::EnableSweepCheck, 0.016f, false);
	}
}

void UMMovementComponent::JumpEnd()
{
	m_bIsJumping = false;
}

void UMMovementComponent::EnableSweepCheck()
{
	m_bDoSweep = true;
}

void UMMovementComponent::EndCoyoteTime()
{
	m_bIsAirborne = true;
}

void UMMovementComponent::CheckAbove()
{
	UWorld* world = GetWorld();
	if (!world) return;
	FHitResult hit;
	FVector start = UpdatedComponent->GetComponentLocation() + (UpdatedComponent->GetUpVector() * 100);
	FVector end = UpdatedComponent->GetUpVector() * 100 + start;
	DrawDebugLine(world, start, end, FColor::Red);

	world->LineTraceSingleByChannel(hit, start, end, ECC_WorldDynamic, m_sweepQueryParams);

	if (AMOneWayPlatform* plat = Cast<AMOneWayPlatform>(hit.GetActor()))
	{
		UBoxComponent* box = Cast<UBoxComponent>(UpdatedComponent);
		box->SetCollisionProfileName("OverlapAllDynamic");
	}
}

void UMMovementComponent::CheckBelow()
{
	UWorld* world = GetWorld();
	if (!world) return;
	FHitResult hit;
	FVector start = UpdatedComponent->GetComponentLocation() + (-UpdatedComponent->GetUpVector() * 100);
	FVector end = -UpdatedComponent->GetUpVector() * 100 + start;
	DrawDebugLine(world, start, end, FColor::Red);

	world->LineTraceSingleByChannel(hit, start, end, ECC_WorldDynamic, m_sweepQueryParams);

	if (hit.GetActor())
	{
		UBoxComponent* box = Cast<UBoxComponent>(UpdatedComponent);
		box->SetCollisionProfileName("BlockAllDynamic");
	}
}

void UMMovementComponent::DropDown()
{
	UWorld* world = GetWorld();
	if (!world) return;
	FHitResult hit;
	FVector start = UpdatedComponent->GetComponentLocation() + (-UpdatedComponent->GetUpVector() * 100);
	FVector end = -UpdatedComponent->GetUpVector() * 100 + start;
	DrawDebugLine(world, start, end, FColor::Red);

	world->LineTraceSingleByChannel(hit, start, end, ECC_WorldDynamic, m_sweepQueryParams);

	if (AMOneWayPlatform* plat = Cast<AMOneWayPlatform>(hit.GetActor()))
	{
		UBoxComponent* box = Cast<UBoxComponent>(UpdatedComponent);
		box->SetCollisionProfileName("OverlapAllDynamic");
	}
}
