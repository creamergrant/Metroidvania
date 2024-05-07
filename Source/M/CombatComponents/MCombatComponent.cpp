// Fill out your copyright notice in the Description page of Project Settings.


#include "MCombatComponent.h"
#include "Components/BoxComponent.h"
#include "MSaveObjInterface.h"

// Sets default values for this component's properties
UMCombatComponent::UMCombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	m_groundAtk1 = CreateDefaultSubobject<UBoxComponent>("GroundAttack1");
	m_groundAtk1->SetRelativeLocation({ 100,0,-30 });
	m_groundAtk1->SetRelativeRotation({ -10,0,0 });
	m_groundAtk1->SetBoxExtent({ 200, 10,30 });
	m_groundAtk1->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
	m_groundAtk1->SetCollisionProfileName("OverlapAll");
	
	m_groundAtk2 = CreateDefaultSubobject<UBoxComponent>("GroundAttack2");
	m_groundAtk2->SetRelativeLocation({ 100,0,30 });
	m_groundAtk2->SetRelativeRotation({ 10,0,0 });
	m_groundAtk2->SetBoxExtent({ 200, 10,30 });
	m_groundAtk2->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
	m_groundAtk2->SetCollisionProfileName("OverlapAll");

	m_groundAtk3 = CreateDefaultSubobject<UBoxComponent>("GroundAttack3");
	m_groundAtk3->SetRelativeLocation({ 100,0,0 });
	m_groundAtk3->SetRelativeRotation({ 0,0,0 });
	m_groundAtk3->SetBoxExtent({ 200, 10,30 });
	m_groundAtk3->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
	m_groundAtk3->SetCollisionProfileName("OverlapAll");

}

void UMCombatComponent::SetAttachmentComponent(USceneComponent* attachment)
{
	m_attachment = attachment;
}


// Called when the game starts
void UMCombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
	if (m_attachment)
	{
		m_groundAtk1->AttachToComponent(m_attachment, FAttachmentTransformRules::KeepRelativeTransform);
		m_groundAtk2->AttachToComponent(m_attachment, FAttachmentTransformRules::KeepRelativeTransform);
		m_groundAtk3->AttachToComponent(m_attachment, FAttachmentTransformRules::KeepRelativeTransform);
	}
}

UBoxComponent* UMCombatComponent::SelectHitBox()
{
	switch (m_attackType)
	{
	case AttackType::Down:

		break;
	case AttackType::Ground:
		switch (m_comboStep)
		{
		case ComboStep::Start:
			return m_groundAtk1;
			break;
		case ComboStep::Middle:
			return m_groundAtk2;
			break;
		case ComboStep::Last:
			return m_groundAtk3;
			break;
		}
		break;
	case AttackType::Air:
		switch (m_comboStep)
		{
		case ComboStep::Start:

			break;
		case ComboStep::Middle:

			break;
		case ComboStep::Last:

			break;
		}
		break;
	case AttackType::Up:

		break;
	default:
		return m_groundAtk1;
		break;
	}
	return m_groundAtk1;
}

// Called every frame
void UMCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (m_attack)
	{
		m_currentHitBox = SelectHitBox();

		TArray<AActor*> actors;
		m_currentHitBox->GetOverlappingActors(actors);
		for (AActor* a : actors)
		{
			if (a->Implements<UMSaveObjInterface>())
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FText::AsNumber((int)m_comboStep).ToString());
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, m_currentHitBox->GetFName().ToString());
			}
		}
		m_attack = false;
	}
}

void UMCombatComponent::Attack()
{
	if (m_comboStep != ComboStep::Last)
	{
		m_comboStep = (ComboStep)((int)m_comboStep + 1);
		m_attack = true;
		GetWorld()->GetTimerManager().ClearTimer(m_resetAttack);
		GetWorld()->GetTimerManager().SetTimer(m_resetAttack, this, &UMCombatComponent::ResetAttack, .5f);
	}
}

void UMCombatComponent::ResetAttack()
{
	m_comboStep = ComboStep::NoAttack;
}

