// Fill out your copyright notice in the Description page of Project Settings.


#include "MPickupBase.h"
#include "Components/BoxComponent.h"
#include "PaperSpriteComponent.h"
#include "MHorizontalSpell.h"
#include "MCharacter.h"

// Sets default values
AMPickupBase::AMPickupBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_collision = CreateDefaultSubobject<UBoxComponent>("Collision");
	m_collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	m_collision->SetCollisionProfileName("OverlapAllDynamic");
	m_collision->SetBoxExtent(FVector(100, 10, 100));
	m_collision->OnComponentBeginOverlap.AddDynamic(this, &AMPickupBase::OnComponentOverlapBegin);
	SetRootComponent(m_collision);

	m_sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	m_sprite->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
	m_sprite->SetCollisionProfileName("NoCollision");
	m_sprite->SetupAttachment(RootComponent);
}

void AMPickupBase::OnPickup()
{
	m_sprite->SetVisibility(false);
	m_collision->OnComponentBeginOverlap.Clear();

	GEngine->AddOnScreenDebugMessage(-11, 2.5f, FColor::Red, "Item Picked Up");
}

// Called when the game starts or when spawned
void AMPickupBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMPickupBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void AMPickupBase::OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !OtherComp || OtherActor == this || OtherComp->GetAttachParentActor() == this)
		return;

	AMCharacter* Character = Cast<AMCharacter>(OtherActor);
	if (Character)
	{
		OnPickup();
		Character->m_spell = NewObject<UMHorizontalSpell>(Character);
	}
}