// Fill out your copyright notice in the Description page of Project Settings.


#include "MPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MSaveGameSubsystem.h"

#include "MTestingObject.h"
#include "Kismet/GameplayStatics.h"
#include "MMovementComponent.h"
#include "MDashComponent.h"
#include "MCharacter.h"
#include "MCombatComponent.h"
#include "Components/BoxComponent.h"
#include "MSpellComponent.h"

void AMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(m_toggleOpenAction, ETriggerEvent::Started, this, &AMPlayerController::ToggleOpen);

		EnhancedInputComponent->BindAction(m_saveAction, ETriggerEvent::Started, this, &AMPlayerController::Save);

		EnhancedInputComponent->BindAction(m_interactAction, ETriggerEvent::Started, this, &AMPlayerController::Interact);
    
		EnhancedInputComponent->BindAction(m_moveAction, ETriggerEvent::Triggered, this, &AMPlayerController::Move);
		EnhancedInputComponent->BindAction(m_moveAction, ETriggerEvent::Completed, this, &AMPlayerController::Move);

		EnhancedInputComponent->BindAction(m_jumpAction, ETriggerEvent::Triggered, this, &AMPlayerController::Jump);

		EnhancedInputComponent->BindAction(m_dashAction, ETriggerEvent::Triggered, this, &AMPlayerController::Dash);

		EnhancedInputComponent->BindAction(m_attackAction, ETriggerEvent::Started, this, &AMPlayerController::Attack);

		EnhancedInputComponent->BindAction(m_spellAction, ETriggerEvent::Started, this, &AMPlayerController::Spell);
	}
}

void AMPlayerController::AcknowledgePossession(APawn* PossesedPawn)
{
	Super::AcknowledgePossession(PossesedPawn);

	m_character = Cast<AMCharacter>(PossesedPawn);
}

void AMPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(this))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(m_mappingContext, 0);
		}
	}

}

void AMPlayerController::ToggleOpen()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMTestingObject::StaticClass(), actors);
	if (actors[0])
	{
		Cast<AMTestingObject>(actors[0])->ToggleOpen();
	}
}

void AMPlayerController::Interact()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMTestingObject::StaticClass(), actors);
	if (actors[0])
	{
		IMInteractInterface::Execute_OnInteract(actors[0]);
	}
}

void AMPlayerController::Save()
{
	UMSaveGameSubsystem* sg = GetGameInstance()->GetSubsystem<UMSaveGameSubsystem>();

	sg->WriteSaveGame();
}

void AMPlayerController::Attack()
{
	m_character->m_combatComp->Attack();
}

void AMPlayerController::Move(const FInputActionValue& Value)
{
	m_currentDirectionalInput.X = Value.Get<float>();

	if (!FMath::IsNearlyZero(m_currentDirectionalInput.X) && !m_bAreMovementControlsLocked)
		m_lastDirectionalInput.X = m_currentDirectionalInput.X;

	if (FMath::IsNearlyZero(m_currentDirectionalInput.X))
	{
		m_character->m_moveComp->Move(Value);
	}
	else if(!m_bAreMovementControlsLocked)
	{
		m_character->m_moveComp->Move(Value);
	}
}

void AMPlayerController::Jump()
{
	if(!m_bAreMovementControlsLocked)
		m_character->m_moveComp->Jump();
}

void AMPlayerController::Dash()
{
	m_character->m_dashComp->Dash();
}

void AMPlayerController::Spell()
{
	if (m_character->m_spell)
	{
		m_character->m_spell->FireSpell();
	}
}

void AMPlayerController::SetMovementControlLockState(bool State)
{
	m_bAreMovementControlsLocked = State;
}
