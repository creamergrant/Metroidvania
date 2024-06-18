// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "MSaveGame.generated.h"


UENUM(meta = (Bitflags))
enum class ESaveComponents
{
	None = 0,
	HorizontalSpell = 1 << 0,
	AcceleratingSpell = 1 << 1,
	DoubleJump = 1 << 2
};

static bool TestBit(uint32 num, ESaveComponents comp)
{
	return (static_cast<uint32>(comp) & num) != 0;
}

static void SetBit(uint32& num, ESaveComponents comp)
{
	num |= 1 << static_cast<uint32>(comp);
}

static void ClearBit(uint32& num, ESaveComponents comp)
{
	num &= ~(1 << static_cast<uint32>(comp));
}

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

	UPROPERTY()
	uint8 m_components;
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
