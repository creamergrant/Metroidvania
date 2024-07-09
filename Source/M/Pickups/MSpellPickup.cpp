// Fill out your copyright notice in the Description page of Project Settings.


#include "MSpellPickup.h"
#include "MCharacter.h"
#include "MPlayerState.h"
#include "MSpellComponent.h"
#include "MHorizontalSpell.h"
#include "MHorizontalSpellProjectile.h"
#include "MAcceleratingSpell.h"
#include "MAcceleratingSpellProjectile.h"

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
				ps->m_components |= static_cast<uint32>(ESaveComponents::AcceleratingSpell);

				UMAcceleratingSpell* spell = NewObject<UMAcceleratingSpell>(Character, ComponentClass);
				spell->m_projectile = AMAcceleratingSpellProjectile::StaticClass();
				Character->m_spells.Add("MAcceleratingSpell", spell);
			}
			if (ComponentClass->GetFName().IsEqual("MHorizontalSpell"))
			{
				ps->m_components |= static_cast<uint32>(ESaveComponents::HorizontalSpell);

				UMHorizontalSpell* spell = NewObject<UMHorizontalSpell>(Character, ComponentClass);
				spell->m_projectile = AMHorizontalSpellProjectile::StaticClass();
				Character->m_spells.Add("MHoriztonalSpell", spell);
			}
		}
		OnPickup();
	}
}