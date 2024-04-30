// Fill out your copyright notice in the Description page of Project Settings.


#include "MTestingObject.h"

// Sets default values
AMTestingObject::AMTestingObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
}

void AMTestingObject::OnActorLoaded_Implementation()
{
	UMaterialInstanceDynamic* MatInst = Cast<AActor>(this)->GetComponentByClass<UPrimitiveComponent>()->CreateAndSetMaterialInstanceDynamic(0);

	if (MatInst)
	{
		MatInst->SetVectorParameterValue("Color", m_color);
	}
}

void AMTestingObject::OnInteract_Implementation()
{
	UMaterialInstanceDynamic* MatInst = Cast<AActor>(this)->GetComponentByClass<UPrimitiveComponent>()->CreateAndSetMaterialInstanceDynamic(0);

	if (MatInst)
	{
		m_color = FLinearColor::MakeRandomColor();
		MatInst->SetVectorParameterValue("Color", m_color);
	}
}

// Called when the game starts or when spawned
void AMTestingObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMTestingObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	m_mesh->SetVisibility(m_open);
	
}

void AMTestingObject::ToggleOpen()
{
	m_open = !m_open;
}

