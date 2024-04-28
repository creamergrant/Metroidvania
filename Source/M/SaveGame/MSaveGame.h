// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MSaveGame.generated.h"

/**
 * 
 */
USTRUCT()
struct FActorSaveData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FTransform m_transform;

	UPROPERTY()
	FName m_name;

	UPROPERTY()
	TArray<uint8> m_byteData;
};

USTRUCT()
struct FPlayerSaveData
{
	GENERATED_BODY()
public:
	FPlayerSaveData()
	{
		m_currency = 0;
		m_location = FVector::ZeroVector;
	}

	UPROPERTY()
	int32 m_currency;

	UPROPERTY()
	FVector m_location;
};

UCLASS()
class M_API UMSaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	UPROPERTY()
	FPlayerSaveData m_savedPlayer;

	UPROPERTY()
	TArray<FActorSaveData> m_savedActors;

	FPlayerSaveData* GetPlayerData() { return &m_savedPlayer; }
};
