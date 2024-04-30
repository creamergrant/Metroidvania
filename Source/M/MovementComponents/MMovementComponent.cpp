// Fill out your copyright notice in the Description page of Project Settings.


#include "MMovementComponent.h"
#include "DrawDebugHelpers.h"

UMMovementComponent::UMMovementComponent()
{
	m_jumpHeight = 100.0f;
	m_bIsAirborne = false;
	m_coyoteTimeAmount = 0.25f;
	m_raycastOffsetDistance = 0.0f;
	m_raycastLength = 10.0f;

	//locks movement to X/Y plane
	PlaneConstraintNormal = GetPlaneConstraintNormalFromAxisSetting(EPlaneConstraintAxisSetting::Y);
}

void UMMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	UWorld* World = GetWorld();
	if (World)
	{
		FHitResult Hit;
		FVector RayStart = UpdatedComponent->GetComponentLocation() + (-UpdatedComponent->GetUpVector() * m_raycastOffsetDistance);
		FVector RayEnd = RayStart + (-UpdatedComponent->GetUpVector() * m_raycastLength);

		bool bFoundHit = World->LineTraceSingleByChannel(Hit, RayStart, RayEnd, ECollisionChannel::ECC_WorldStatic);
		DrawDebugLine(World, RayStart, RayEnd, FColor::Red, false, -1, 0, 5);

		if (bFoundHit == false && World->GetTimerManager().IsTimerActive(m_coyoteTimeTimer) == false && m_bIsAirborne == false)
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
