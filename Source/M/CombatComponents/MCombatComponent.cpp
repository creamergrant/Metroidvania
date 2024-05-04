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
	m_groundAtk1->SetRelativeLocation({ 100,0,0 });
	m_groundAtk1->SetBoxExtent({ 200, 10,30 });
	m_groundAtk1->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
	m_groundAtk1->SetCollisionProfileName("OverlapAll");
	

}


// Called when the game starts
void UMCombatComponent::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void UMCombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (m_attack)
	{
		TArray<AActor*> actors;
		m_groundAtk1->GetOverlappingActors(actors);
		for (AActor* a : actors)
		{
			if (a->Implements<UMSaveObjInterface>())
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FText::AsNumber((int)m_comboStep).ToString());
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

