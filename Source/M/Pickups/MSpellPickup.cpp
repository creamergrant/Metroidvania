// Fill out your copyright notice in the Description page of Project Settings.


#include "MSpellPickup.h"
#include "MCharacter.h"
#include "MPlayerState.h"
#include "MSpellComponent.h"

AMSpellPickup::AMSpellPickup()
{
}

void AMSpellPickup::OnPickup()
{
	Super::OnPickup();
}

void AMSpellPickup::BeginPlay()
{
	Super::BeginPlay();
}

void AMSpellPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMSpellPickup::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !OtherComp || OtherActor == this || OtherComp->GetAttachParentActor() == this)
		return;

	AMCharacter* Character = Cast<AMCharacter>(OtherActor);
	if (Character)
	{
		AMPlayerState* ps = Cast<AMPlayerState>(Character->GetPlayerState());
		if (ps)
		{
			if (ComponentClass->GetFName().IsEqual("MAcceleratingSpell"))
			{
				SetBit(ps->m_components, ESaveComponents::AcceleratingSpell);
			}
			if (ComponentClass->GetFName().IsEqual("MHorizontalSpell"))
			{
				SetBit(ps->m_components, ESaveComponents::HorizontalSpell);
			}
		}
		Character->m_spell = NewObject<UMSpellComponent>(Character, ComponentClass);
		Character->m_spell->RegisterComponent();
		OnPickup();
	}
}