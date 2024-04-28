// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MPlayerState.generated.h"

class UMSaveGame;

/**
 * 
 */
UCLASS()
class M_API AMPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AMPlayerState();

	UPROPERTY(EditDefaultsOnly, Category = "Currency")
	int32 m_currency;

	void LoadPlayerState(UMSaveGame* SaveObject);

	void SavePlayerState(UMSaveGame* SaveObject);
};
