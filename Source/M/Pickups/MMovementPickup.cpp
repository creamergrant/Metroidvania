// Fill out your copyright notice in the Description page of Project Settings.


#include "MMovementPickup.h"
#include "MCharacter.h"
#include "MPlayerState.h"

AMMovementPickup::AMMovementPickup()
{
}

void AMMovementPickup::OnPickup()
{
	Super::OnPickup();
}

void AMMovementPickup::BeginPlay()
{
	Super::BeginPlay();
}

void AMMovementPickup::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !OtherComp || OtherActor == this || OtherComp->GetAttachParentActor() == this)
		return;

	AMCharacter* Character = Cast<AMCharacter>(OtherActor);
	if (Character)
	{
		AMPlayerState* ps = Cast<AMPlayerState>(Character->GetPlayerState());
		if (ps)
		{
			if (m_component->GetFName().IsEqual("MDoubleJumpComponent"))
			{
				SetBit(ps->m_components, ESaveComponents::DoubleJump);
			}
		}
		Character->m_movementComps.Add(NewObject<USceneComponent>(Character, m_component));
		OnPickup();
	}
}

void AMMovementPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
