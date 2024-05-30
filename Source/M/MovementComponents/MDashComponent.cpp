// Fill out your copyright notice in the Description page of Project Settings.


#include "MDashComponent.h"
#include "MCharacter.h"
#include "MPlayerController.h"

UMDashComponent::UMDashComponent()
{
	m_bCanDash = true;
	m_bIsDashing = false;
	m_dashDirection = 1.0f;
	m_dashCooldownTimeAmount = 5.0f;
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

		FVector Delta = { -m_dashDirection * m_dashImpulseValue * DeltaTime, 0.0f, 0.0000001f };
		MoveUpdatedComponent(Delta, UpdatedPrimitive->GetComponentRotation(), true);
	}
}

void UMDashComponent::Dash()
{
	if (!m_bCanDash)
		return;

	Character->StopAllMovement();

	//UpdatedPrimitive->SetSimulatePhysics(false);

	PC->SetMovementControlLockState(true);
	m_dashDirection = PC->GetLastDirectionalInput().X;

	m_bIsDashing = true;
	m_bCanDash = false;

	GetWorld()->GetTimerManager().SetTimer(m_dashDurationTimer, this, &UMDashComponent::EndDash, m_dashDurationTimeAmount, false);
}

void UMDashComponent::EndDash()
{
	Character->StopAllMovement();

	PC->SetMovementControlLockState(false);
		
	m_bIsDashing = false;

	GetWorld()->GetTimerManager().SetTimer(m_dashDurationTimer, this, &UMDashComponent::EnableCanDash, m_dashCooldownTimeAmount, false);

	//UpdatedPrimitive->SetSimulatePhysics(true);
}

void UMDashComponent::EnableCanDash()
{
	m_bCanDash = true;
}
