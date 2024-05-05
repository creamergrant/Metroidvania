// Fill out your copyright notice in the Description page of Project Settings.


#include "MMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Components/BoxComponent.h"

UMMovementComponent::UMMovementComponent()
{
	m_jumpHeight = 100.0f;
	m_bIsAirborne = false;
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
		FVector HalfExtent = Box->GetScaledBoxExtent() * 0.5f;
		FVector3f RealHalfExtent = { (float)HalfExtent.X, (float)HalfExtent.Y, (float)HalfExtent.Z };
		m_sweepShape.SetBox(RealHalfExtent);
	}

	m_sweepQueryParams.AddIgnoredComponent(UpdatedPrimitive);
}

void UMMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UWorld* World = GetWorld();
	if (World)
	{
		FHitResult Hit;
		FVector RayStart = UpdatedComponent->GetComponentLocation() + (-UpdatedComponent->GetUpVector() * m_sweepStartOffset);
		FVector RayEnd = RayStart + (-UpdatedComponent->GetUpVector() * m_sweepDistance);

		bool bFoundHit = World->SweepTestByChannel(RayStart, RayEnd, UpdatedPrimitive->GetComponentQuat(), ECollisionChannel::ECC_WorldStatic, m_sweepShape, m_sweepQueryParams);
		DrawDebugLine(World, RayStart, RayEnd, FColor::Red, false, -1, 0, 5);

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
}

void UMMovementComponent::Move(const FInputActionValue&)
{

}

void UMMovementComponent::Jump()
{
	if (UpdatedPrimitive && !m_bIsAirborne)
	{
		UpdatedPrimitive->AddImpulse(FVector::UpVector * m_jumpHeight);
		m_bIsAirborne = true;
	}
}

void UMMovementComponent::EndCoyoteTime()
{
	m_bIsAirborne = true;
}
