// Fill out your copyright notice in the Description page of Project Settings.


#include "MEnemyBase.h"
#include "Components/BoxComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "MCharacter.h"

AMEnemyBase::AMEnemyBase()
{
	m_bIsWalking = false;
	m_walkSpeed = 100.0f;
	m_direction = GetActorForwardVector();

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
}

void AMEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_bIsWalking)
	{
		FVector Delta = (m_direction * m_walkSpeed) * DeltaTime;
		GetCharacterMovement()->MoveUpdatedComponent(Delta, GetActorRotation(), true);
	}
}

void AMEnemyBase::SetIsWalking(bool bIsWalking)
{
	m_bIsWalking = bIsWalking;
}

bool AMEnemyBase::GetIsWalking()
{
	return m_bIsWalking;
}

void AMEnemyBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMEnemyBase::ComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<AMCharacter>(OtherActor)) return;
	m_direction = -m_direction;
	SetActorRotation(FQuat(m_direction.Rotation()));
}

void AMEnemyBase::ComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<AMCharacter>(OtherActor)) return;
	m_direction = -m_direction;
	SetActorRotation(FQuat(m_direction.Rotation()));
}
