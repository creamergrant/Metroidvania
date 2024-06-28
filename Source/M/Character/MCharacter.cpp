// Fill out your copyright notice in the Description page of Project Settings.


#include "MCharacter.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MMovementComponent.h"
#include "MDashComponent.h"
#include "MCombatComponent.h"
#include "MEquipable.h"
#include "MPlayerState.h"
#include "MHorizontalSpell.h"
#include "MAcceleratingSpell.h"
#include "MSaveGame.h"
#include "MDoubleJumpComponent.h"
#include "MAnimationComponent.h"

// Sets default values
AMCharacter::AMCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_movement = CreateDefaultSubobject<UBoxComponent>("movementComp");
	m_movement->SetSimulatePhysics(true);
	m_movement->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_movement->SetCollisionProfileName("BlockAllDynamic");
	m_movement->SetBoxExtent(FVector(100, 10, 100));
	m_movement->BodyInstance.bLockXRotation = true;
	m_movement->BodyInstance.bLockYRotation = true;
	m_movement->BodyInstance.bLockZRotation = true;
	m_movement->BodyInstance.bLockYTranslation = true;
	SetRootComponent(m_movement);

	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	m_mesh->SetSimulatePhysics(false);
	m_mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_mesh->SetCollisionProfileName("NoCollision");
	m_mesh->SetupAttachment(RootComponent);

	m_springArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	m_springArm->SetupAttachment(RootComponent);
	m_springArm->SocketOffset = FVector(0, 0, 300);
	m_springArm->SetRelativeRotation(FRotator(0, -90.0f, 0));
	m_springArm->TargetArmLength = 500.0f;
	m_springArm->bEnableCameraLag = false;
	m_springArm->CameraLagSpeed = 30.0f;

	m_camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	m_camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	m_camera->SetOrthoWidth(5000.0f);
	m_camera->SetupAttachment(m_springArm);
	m_camera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	m_moveComp = CreateDefaultSubobject<UMMovementComponent>("MoveComp");
	m_moveComp->UpdatedComponent = m_movement;

	m_dashComp = CreateDefaultSubobject<UMDashComponent>("DashComp");

	m_aniComp = CreateDefaultSubobject<UMAnimationComponent>("AnimationComp");
	m_aniComp->SetupAttachment(m_movement);

	m_combatComp = CreateDefaultSubobject<UMCombatComponent>("CombatComp");
	m_combatComp->SetupAttachment(m_aniComp);
	m_combatComp->SetVisibility(true);
}

FRotator AMCharacter::GetSpellDirection()
{
	return (m_aniComp->GetRelativeRotation().Vector() * FRotator(0,180,0).Vector()).Rotation();
}

// Called when the game starts or when spawned
void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
	if (AMPlayerState* ps = Cast<AMPlayerState>(GetPlayerState()))
	{
		if (TestBit(ps->m_components, ESaveComponents::HorizontalSpell))
		{
			UMSpellComponent* spell = NewObject<UMHorizontalSpell>();
			spell->Rename(new TCHAR('a'), this);
			spell->RegisterComponent();
			m_spells.Add("MHorizontalSpell", spell);
		}
		if (TestBit(ps->m_components, ESaveComponents::AcceleratingSpell))
		{
			UMSpellComponent* spell = NewObject<UMAcceleratingSpell>();
			spell->Rename(new TCHAR('a'), this);
			spell->RegisterComponent();
			m_spells.Add("MAcceleratingSpell", spell);
		}
		if (TestBit(ps->m_components, ESaveComponents::DoubleJump))
		{
			m_movementComps.Add(FString("MDoubleJumpComponent"), NewObject<UMDoubleJumpComponent>());
		}
	}
}

// Called every frame
void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, DeltaTime, FColor::Blue, FString::FromInt(m_mana));
}

void AMCharacter::IncreaseStats()
{
	for (int i = 0; i < m_equips.Num(); i++)
	{
		for (int j = 0; j < m_equips[i]->m_stats.Num(); j++)
		{
			float inc = m_equips[i]->m_stats[j]->m_increaseAmt;
			switch (m_equips[i]->m_stats[j]->m_type)
			{
			case StatType::NoIncrease:
				
				break;
			case StatType::Movement:
				m_movementStat += inc;
				break;
			case StatType::Damage:
				m_dmgStat += inc;
				break;
			case StatType::Health:
				m_healthStat += inc;
				break;
			case StatType::Weight:
				m_weightStat += inc;
				break;
			case StatType::Strength:
				m_strengthStat += inc;
				break;
			case StatType::AttackSpeed:
				m_atkSpeedStat += inc;
				break;
			default:

				break;
			}
		}
	}
}

FVector2D AMCharacter::GetMovementValue()
{
	return m_moveComp->GetMovementValue();
}

bool AMCharacter::GetIsAirborne()
{
	return m_moveComp->GetIsAirborne();
}

bool AMCharacter::GetIsJumping()
{
	return m_moveComp->GetIsJumping();
}

bool AMCharacter::GetIsDashing()
{
	return m_dashComp->GetIsDashing();
}

bool AMCharacter::GetIsAttacking()
{
	return m_combatComp->GetIsAttacking();
}

void AMCharacter::SetCanAttack(bool canAttack)
{
	m_combatComp->m_canAttack = canAttack;
}

void AMCharacter::IncreaseMana(int add)
{
	m_mana += add;
	if (m_mana > m_maxMana)
		m_mana = m_maxMana;
}

void AMCharacter::SetMana(int mana)
{
	m_mana = mana;
	if (m_mana > m_maxMana)
		m_mana = m_maxMana;
}

void AMCharacter::DecreaseMana(int sub)
{
	m_mana -= sub;
	if (m_mana < 0)
		m_mana = 0;
}

void AMCharacter::IncreaseHealth(int add)
{
	m_health += add;
	if (m_health < m_maxHealth)
		m_health = m_maxHealth;
}

void AMCharacter::SetHealth(int health)
{
	m_health = health;
	if (m_health > m_maxHealth)
		m_health = m_maxHealth;
}

void AMCharacter::DecreaseHealth(int sub)
{
	m_health -= sub;
	if (m_health < 0)
		m_health = 0;
}

