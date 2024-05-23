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

	FString packName = TEXT("Metroidvania/Content/Mesh/the_guy2");
	FString objName = TEXT("the_guy2");

	m_mesh = LoadObject<UStaticMesh>(nullptr, *packName, *objName);
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
		AMHorizontalSpellProjectile* projectile = GetWorld()->SpawnActor<AMHorizontalSpellProjectile>(m_projectile, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), params);


		projectile->m_mesh->SetStaticMesh(m_mesh);
	}
}
