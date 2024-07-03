// Fill out your copyright notice in the Description page of Project Settings.


#include "MAnimationComponent.h"
#include "PaperFlipbook.h"
#include "PaperFlipbookComponent.h"
#include "MCharacter.h"
#include "MCombatComponent.h"

// Sets default values for this component's properties
UMAnimationComponent::UMAnimationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	m_sprite = CreateDefaultSubobject<UPaperFlipbookComponent>("Sprite");
	m_sprite->AlwaysLoadOnClient = true;
	m_sprite->AlwaysLoadOnServer = true;
	m_sprite->bOwnerNoSee = false;
	m_sprite->bAffectDynamicIndirectLighting = true;
	m_sprite->PrimaryComponentTick.TickGroup = TG_PrePhysics;
	static FName CollisionProfileName(TEXT("NoCollision"));
	m_sprite->SetCollisionProfileName(CollisionProfileName);
	m_sprite->SetGenerateOverlapEvents(false);
}


// Called when the game starts
void UMAnimationComponent::BeginPlay()
{
	Super::BeginPlay();

	m_character = Cast<AMCharacter>(GetOwner());
	m_sprite->OnFinishedPlaying.AddDynamic(this, &UMAnimationComponent::OnFinshedPlaying);
}

void UMAnimationComponent::OnRegister()
{
	Super::OnRegister();

	m_sprite->SetupAttachment(this);
}

// Called every frame
void UMAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (m_character)
	{
		FVector2D moveVal = m_character->GetMovementValue();
		if (moveVal.X > 0)
			SetRelativeRotation(FRotator(0, 180, 0));
		else if (moveVal.X < 0)
			SetRelativeRotation(FRotator::ZeroRotator);
	}
	UpdateAnimation();
}

void UMAnimationComponent::UpdateAnimation()
{
	if (m_character->GetIsDashing())
	{
		SwapAnimation(m_dashAnim);
	}
	else if (m_character->GetIsJumping() && !m_attackAnimation)
	{
		SwapAnimation(m_jumpAnim);
	}
	else
	{
		if (m_character->GetIsAttacking())
		{
			SwapAnimation(m_attackAnimations[m_character->GetActiveHitBoxName()], false);
			m_attackAnimation = true;
		}
		else if (!m_attackAnimation)
		{
			if (m_character->GetIsAirborne())
			{
				SwapAnimation(m_fallingAnim);
			}
			else if (m_character->GetMovementValue().X != 0)
			{
				SwapAnimation(m_walkAnim);
			}
			else
			{
				SwapAnimation(m_idleAnim);
			}
		}
	}
}

void UMAnimationComponent::SwapAnimation(UPaperFlipbook* anim, bool looping)
{
	m_sprite->SetFlipbook(anim);
	m_sprite->SetLooping(looping);
	m_sprite->Play();
}

void UMAnimationComponent::OnFinshedPlaying()
{
	m_attackAnimation = false;
	m_character->SetCanAttack(true);
}

void UMAnimationComponent::IncreaseMana(int add)
{
	m_character->IncreaseMana(add);
}

