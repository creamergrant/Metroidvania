// Fill out your copyright notice in the Description page of Project Settings.


#include "MEnemyBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AMEnemyBase::AMEnemyBase()
{
	m_ledgeDetector = CreateDefaultSubobject<UBoxComponent>("LedgeDetector");
	m_ledgeDetector->SetupAttachment(RootComponent);
	m_ledgeDetector->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
	m_ledgeDetector->SetCollisionProfileName("OverlapAll");
	m_ledgeDetector->OnComponentEndOverlap.AddDynamic(this, &AMEnemyBase::ComponentOverlapEnd);

	m_wallDetector = CreateDefaultSubobject<UBoxComponent>("WallDetector");
	m_wallDetector->SetupAttachment(RootComponent);
	m_wallDetector->SetCollisionEnabled(ECollisionEnabled::QueryAndProbe);
	m_wallDetector->SetCollisionProfileName("OverlapAll");
	m_wallDetector->OnComponentBeginOverlap.AddDynamic(this, &AMEnemyBase::ComponentOverlapBegin);

	m_direction = GetActorForwardVector();
}

void AMEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Delta = (m_direction * 50) * DeltaTime;
	GetCharacterMovement()->MoveUpdatedComponent(Delta, GetActorRotation(), true);
}

void AMEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMEnemyBase::ComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	m_direction = -m_direction;
	SetActorRotation(FQuat(m_direction.Rotation()));
}

void AMEnemyBase::ComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	m_direction = -m_direction;
	SetActorRotation(FQuat(m_direction.Rotation()));
}
