// Fill out your copyright notice in the Description page of Project Settings.


#include "MPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MSaveGameSubsystem.h"

#include "MTestingObject.h"
#include "Kismet/GameplayStatics.h"
#include "MMovementComponent.h"
#include "MCharacter.h"

void AMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(m_toggleOpenAction, ETriggerEvent::Started, this, &AMPlayerController::ToggleOpen);

		EnhancedInputComponent->BindAction(m_saveAction, ETriggerEvent::Started, this, &AMPlayerController::Save);

		EnhancedInputComponent->BindAction(m_interactAction, ETriggerEvent::Started, this, &AMPlayerController::Interact);
    
		EnhancedInputComponent->BindAction(m_moveAction, ETriggerEvent::Triggered, this, &AMPlayerController::Move);
		EnhancedInputComponent->BindAction(m_jumpAction, ETriggerEvent::Triggered, this, &AMPlayerController::Jump);
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
		IMSaveObjInterface::Execute_OnInteract(actors[0]);
	}
}

void AMPlayerController::Save()
{
	UMSaveGameSubsystem* sg = GetGameInstance()->GetSubsystem<UMSaveGameSubsystem>();

	sg->WriteSaveGame();
}

void AMPlayerController::Move(const FInputActionValue&)
{
}

void AMPlayerController::Jump()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AMTestingObject::StaticClass(), actors);
	if (actors[0])
	{
		Cast<AMTestingObject>(actors[0])->m_moveComp->Jump();
	}
	m_character->m_moveComp->Jump();
}
