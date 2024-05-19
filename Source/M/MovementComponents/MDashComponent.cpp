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
}

void UMDashComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_bIsDashing)
	{
		FVector Delta = { -m_dashDirection * m_dashImpulseValue * DeltaTime, 0.0f, 0.0000001f }; //Need that added z value or the character gets stuck on ledges from the sweep.
		UpdatedPrimitive->SetWorldLocation(UpdatedPrimitive->GetComponentLocation() + Delta, true); //Need the sweep or character can sort of stick to walls
	}
}

void UMDashComponent::Dash()
{
	if (!m_bCanDash)
		return;

	UpdatedPrimitive->SetEnableGravity(false);

	AMCharacter* Character = Cast<AMCharacter>(UpdatedPrimitive->GetAttachmentRootActor());
	if (Character)
	{
		Character->StopAllMovement();

		AMPlayerController* PC = Cast<AMPlayerController>(Character->Controller);
		if (PC)
		{
			PC->SetMovementControlLockState(true);
			m_dashDirection = PC->GetLastDirectionalInput().X;
		}
	}

	m_bIsDashing = true;
	m_bCanDash = false;

	GetWorld()->GetTimerManager().SetTimer(m_dashDurationTimer, this, &UMDashComponent::EndDash, m_dashDurationTimeAmount, false);
}

void UMDashComponent::EndDash()
{
	UpdatedPrimitive->SetEnableGravity(true);

	AMCharacter* Character = Cast<AMCharacter>(UpdatedPrimitive->GetAttachmentRootActor());
	if (Character)
	{
		Character->StopAllMovement();

		AMPlayerController* PC = Cast<AMPlayerController>(Character->Controller);
		if (PC)
		{
			PC->SetMovementControlLockState(false);
		}
	}

	m_bIsDashing = false;

	GetWorld()->GetTimerManager().SetTimer(m_dashDurationTimer, this, &UMDashComponent::EnableCanDash, m_dashCooldownTimeAmount, false);
}

void UMDashComponent::EnableCanDash()
{
	m_bCanDash = true;
}
