// Fill out your copyright notice in the Description page of Project Settings.


#include "MAcceleratingSpell.h"
#include "MAcceleratingSpellProjectile.h"
#include "UObject/ConstructorHelpers.h"

UMAcceleratingSpell::UMAcceleratingSpell()
{

}

void UMAcceleratingSpell::BeginPlay()
{
	Super::BeginPlay();
	m_projectile = AMAcceleratingSpellProjectile::StaticClass();
}

void UMAcceleratingSpell::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMAcceleratingSpell::OnRegister()
{
	Super::OnRegister();
}

void UMAcceleratingSpell::FireSpell()
{
	if (m_projectile)
	{
		FActorSpawnParameters params;
		params.Owner = this->GetOwner();
		GetWorld()->SpawnActor<AMAcceleratingSpellProjectile>(m_projectile, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), params);
	}
}
