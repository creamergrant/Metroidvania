// Fill out your copyright notice in the Description page of Project Settings.


#include "MHorizontalSpell.h"
#include "MHorizontalSpellProjectile.h"
#include "UObject/ConstructorHelpers.h"

UMHorizontalSpell::UMHorizontalSpell()
{
	
}

void UMHorizontalSpell::BeginPlay()
{
	Super::BeginPlay();
	m_projectile = AMHorizontalSpellProjectile::StaticClass();
}

void UMHorizontalSpell::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UMHorizontalSpell::OnRegister()
{
	Super::OnRegister();
}

void UMHorizontalSpell::FireSpell()
{
	if (m_projectile)
	{
		FActorSpawnParameters params;
		params.Owner = this->GetOwner();
		GetWorld()->SpawnActor<AMHorizontalSpellProjectile>(m_projectile, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), params);
	}
}
