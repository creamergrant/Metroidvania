// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "MSaveGameSubsystem.generated.h"

class UMSaveGame;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSaveGameSignature, UMSaveGame*, SaveObject);
/**
 *
 */
UCLASS(meta = (DisplayName = "SaveGame System"))
class M_API UMSaveGameSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	FString m_currentSlotName;

	UPROPERTY()
	UMSaveGame* m_currentSaveGame;

public:

	void HandlePlayer(AController* NewPlayer);

	UFUNCTION(BlueprintCallable)
	bool OverrideSpawnTransform(AController* NewPlayer);

	UFUNCTION(BlueprintCallable)
	void SetSlotName(FString slotname = "");

	UFUNCTION(BlueprintCallable, Category = "SaveGame")
	void WriteSaveGame();

	void LoadSaveGame(FString InSlotName = "");

	UPROPERTY(BlueprintAssignable)
	FOnSaveGameSignature OnSaveGameLoaded;

	UPROPERTY(BlueprintAssignable)
	FOnSaveGameSignature OnSaveGameWritten;

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
};
