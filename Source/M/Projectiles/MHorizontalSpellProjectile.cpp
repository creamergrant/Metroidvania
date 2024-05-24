// Fill out your copyright notice in the Description page of Project Settings.


#include "MHorizontalSpellProjectile.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "MSaveObjInterface.h"
#include "MTestingObject.h"

AMHorizontalSpellProjectile::AMHorizontalSpellProjectile()
{
	m_hitBox = CreateDefaultSubobject<UBoxComponent>("HitBox");
	m_hitBox->SetBoxExtent({ 100,100,100 });
	m_hitBox->SetEnableGravity(false);
	m_hitBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_hitBox->SetCollisionProfileName("OverlapDynamic");

	SetRootComponent(m_hitBox);

	m_hitBox->OnComponentBeginOverlap.AddDynamic(this, &AMHorizontalSpellProjectile::OnBeginOverlap);

	SetRootComponent(m_hitBox);

	m_moveComp = CreateDefaultSubobject<UProjectileMovementComponent>("MoveComp");
	m_moveComp->UpdatedComponent = m_hitBox;
	m_moveComp->InitialSpeed = 100.0f;
	m_moveComp->MaxSpeed = 1000.0f;
	m_moveComp->bRotationFollowsVelocity = false;
	m_moveComp->ProjectileGravityScale = 0;

	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Mesh/the_guy2"));

	m_mesh->SetStaticMesh(MeshObj.Object);
	
	m_mesh->SetupAttachment(RootComponent);
}

void AMHorizontalSpellProjectile::BeginPlay()
{
	Super::BeginPlay();
}

void AMHorizontalSpellProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMHorizontalSpellProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMTestingObject>(Other))
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Blue, "git gud");
	}
}
