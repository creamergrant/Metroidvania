// Fill out your copyright notice in the Description page of Project Settings.


#include "MMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"
#include "InputActionValue.h"

UMMovementComponent::UMMovementComponent()
{
	m_movementValue = 0.0f;
	m_movementSpeed = 500.0f;

	m_jumpHeight = 100.0f;
	m_bIsAirborne = false;
	m_bDoSweep = true;
	m_coyoteTimeAmount = 0.25f;
	m_sweepStartOffset = 0.0f;
	m_sweepDistance = 100.0f;

	//locks movement to X/Y plane
	bConstrainToPlane = true;
	PlaneConstraintNormal = GetPlaneConstraintNormalFromAxisSetting(EPlaneConstraintAxisSetting::Y);
}

void UMMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	UBoxComponent* Box = Cast<UBoxComponent>(UpdatedPrimitive);
	if (Box)
	{
		FVector HalfExtent = Box->GetScaledBoxExtent() / 2.0f;
		FVector3f RealHalfExtent = { (float)HalfExtent.X, (float)HalfExtent.Y, (float)HalfExtent.Z };
		m_sweepShape.SetBox(RealHalfExtent);
	}

	m_sweepQueryParams.AddIgnoredComponent(UpdatedPrimitive);
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
	
	if (!FMath::IsNearlyZero(m_movementValue))
	{
		FVector Delta = { -m_movementValue * m_movementSpeed * DeltaTime, 0.0f, 0.0000001f }; //Need that added z value or the character gets stuck on ledges from the sweep.
		UpdatedPrimitive->SetWorldLocation(UpdatedPrimitive->GetComponentLocation() + Delta, true); //Need the sweep or character can sort of stick to walls
	}
	GEngine->AddOnScreenDebugMessage(-10, 1.f, FColor::Red, FString::SanitizeFloat(m_movementValue));
}

void UMMovementComponent::Move(const FInputActionValue& Value)
{
	m_movementValue = Value.Get<float>();
}

void UMMovementComponent::Jump()
{
	if (UpdatedPrimitive && !m_bIsAirborne)
	{
		StopMovementImmediately(); //Makes the jump feel a little more consistent. Zeros velocity so the jump impulse isnt fighting against downward velocity.

		UpdatedPrimitive->AddImpulse(FVector::UpVector * m_jumpHeight);
		m_bIsAirborne = true;
		m_bDoSweep = false;

		FTimerHandle SweepEnable;
		GetWorld()->GetTimerManager().SetTimer(SweepEnable, this, &UMMovementComponent::EnableSweepCheck, 0.016f, false);
	}
}

void UMMovementComponent::EnableSweepCheck()
{
	m_bDoSweep = true;
}

void UMMovementComponent::EndCoyoteTime()
{
	m_bIsAirborne = true;
}

