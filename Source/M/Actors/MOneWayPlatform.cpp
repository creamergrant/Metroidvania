// Fill out your copyright notice in the Description page of Project Settings.


#include "MOneWayPlatform.h"
#include "Components/BoxComponent.h"

// Sets default values
AMOneWayPlatform::AMOneWayPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_hitBox = CreateDefaultSubobject<UBoxComponent>("hitBox");
	m_hitBox->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_hitBox->SetEnableGravity(false);
	m_hitBox->SetCollisionProfileName("BlockAll");
	m_hitBox->SetBoxExtent({ 150,25,25 });

	SetRootComponent(m_hitBox);

	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");

	m_mesh->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AMOneWayPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMOneWayPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

