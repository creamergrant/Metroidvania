// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class M_API AMGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMGameModeBase();

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer);
};
