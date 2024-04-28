// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DeveloperSettings.h"
#include "MSaveSettings.generated.h"

/**
 * 
 */
UCLASS(Config = Game, defaultconfig, meta = (DisplayName = "Save Game Settings"))
class M_API UMSaveSettings : public UDeveloperSettings
{
	GENERATED_BODY()

public:
	UMSaveSettings()
	{
		m_saveSlotName = "SaveGame02";
	}

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General")
	FString m_saveSlotName;

	UPROPERTY(Config, EditAnywhere, BlueprintReadOnly, Category = "General", AdvancedDisplay)
	TSoftObjectPtr<UDataTable> m_dummyTablePath;

};