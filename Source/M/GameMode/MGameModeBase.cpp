// Fill out your copyright notice in the Description page of Project Settings.


#include "MGameModeBase.h"
#include "MSaveGameSubsystem.h"
#include "Kismet/GameplayStatics.h"

AMGameModeBase::AMGameModeBase() :
	AGameModeBase()
{
}

void AMGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	UMSaveGameSubsystem* sg = GetGameInstance()->GetSubsystem<UMSaveGameSubsystem>();

	FString selectedSaveSlot = UGameplayStatics::ParseOption(Options, "SaveGame");
	sg->LoadSaveGame(selectedSaveSlot);
}

void AMGameModeBase::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
	UMSaveGameSubsystem* sg = GetGameInstance()->GetSubsystem<UMSaveGameSubsystem>();
	sg->HandlePlayer(NewPlayer);

	Super::HandleStartingNewPlayer_Implementation(NewPlayer);

	sg->OverrideSpawnTransform(NewPlayer);
}