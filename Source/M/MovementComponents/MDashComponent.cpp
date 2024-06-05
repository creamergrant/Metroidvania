// Fill out your copyright notice in the Description page of Project Settings.


#include "MDashComponent.h"
#include "MCharacter.h"
#include "MPlayerController.h"

UMDashComponent::UMDashComponent()
{
	m_bCanDash = true;
	m_bIsDashing = false;
	m_dashDirection = 1.0f;
	m_dashCooldownTimeAmount = 1.0f; //absolute max, 5.0 is insane
	m_dashDurationTimeAmount = 0.5f;
	m_dashImpulseValue = 10000.0f;

	bConstrainToPlane = true;
	PlaneConstraintNormal = GetPlaneConstraintNormalFromAxisSetting(EPlaneConstraintAxisSetting::Y);


}

void UMDashComponent::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<AMCharacter>(UpdatedPrimitive->GetAttachmentRootActor());
	if (Character)
	{
		PC = Cast<AMPlayerController>(Character->Controller);
	}
}

void UMDashComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_bIsDashing)
	{
		FHitResult Hit;
		FVector Delta = { -m_dashDirection * m_dashImpulseValue * DeltaTime, 0.0f, 0.0000001f };
		MoveUpdatedComponent(Delta, UpdatedPrimitive->GetComponentRotation(), true, &Hit, ETeleportType::TeleportPhysics);

		if (Hit.bBlockingHit) // if youve hit something solid, stop the dash.
		{
			m_bIsDashing = false;
			GetWorld()->GetTimerManager().ClearTimer(m_dashDurationTimer);
			EndDash();
		}
	}
}

void UMDashComponent::Dash()
{
	if (!m_bCanDash)
		return;

	UpdatedPrimitive->SetSimulatePhysics(false); //stops physics for the character

	PC->SetMovementControlLockState(true);
	m_dashDirection = PC->GetLastDirectionalInput().X;

	m_bIsDashing = true;
	m_bCanDash = false;

	GetWorld()->GetTimerManager().SetTimer(m_dashDurationTimer, this, &UMDashComponent::EndDash, m_dashDurationTimeAmount, false);
}

void UMDashComponent::EndDash()
{
	PC->SetMovementControlLockState(false);
		
	m_bIsDashing = false;

	GetWorld()->GetTimerManager().SetTimer(m_dashDurationTimer, this, &UMDashComponent::EnableCanDash, m_dashCooldownTimeAmount, false);

	UpdatedPrimitive->SetSimulatePhysics(true); //resumes physics for the character
}

void UMDashComponent::EnableCanDash()
{
	m_bCanDash = true;
}
