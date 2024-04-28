// Fill out your copyright notice in the Description page of Project Settings.


#include "MMovementComponent.h"

UMMovementComponent::UMMovementComponent()
{
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

		if (bFoundHit == false && World->GetTimerManager().IsTimerActive(m_coyoteTimeTimer) == false && m_bIsAirborne == false)
		{
			World->GetTimerManager().SetTimer(m_coyoteTimeTimer, this, UMMovementComponent::EndCoyoteTime, m_coyoteTimeAmount, false);
		}
	}
}

void UMMovementComponent::Move(const FInputActionValue&)
{

}

void UMMovementComponent::Jump()
{
}

void UMMovementComponent::EndCoyoteTime()
{
	m_bIsAirborne = true;
}
