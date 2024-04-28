// Fill out your copyright notice in the Description page of Project Settings.


#include "MPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MSaveGameSubsystem.h"

#include "MTestingObject.h"
#include "Kismet/GameplayStatics.h"

void AMPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(m_toggleOpenAction, ETriggerEvent::Started, this, &AMPlayerController::ToggleOpen);

		EnhancedInputComponent->BindAction(m_saveAction, ETriggerEvent::Started, this, &AMPlayerController::Save);
	}
}

void AMPlayerController::AcknowledgePossession(APawn* PossesedPawn)
{
	Super::AcknowledgePossession(PossesedPawn);
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

void AMPlayerController::Save()
{
	UMSaveGameSubsystem* sg = GetGameInstance()->GetSubsystem<UMSaveGameSubsystem>();

	sg->WriteSaveGame();
}
