// Fill out your copyright notice in the Description page of Project Settings.


#include "MPlayerState.h"
#include "MSaveGame.h"
#include "MCharacter.h"

AMPlayerState::AMPlayerState() :
	APlayerState()
{

}

void AMPlayerState::LoadPlayerState(UMSaveGame* SaveObject)
{
	if (SaveObject)
	{
		FPlayerSaveData* data = SaveObject->GetPlayerData();
		if (data)
		{
			m_currency = data->m_currency;
			m_components = data->m_components;
		}
		else
		{
			//sadness
		}
	}
}

void AMPlayerState::SavePlayerState(UMSaveGame* SaveObject)
{
	if (SaveObject)
	{
		FPlayerSaveData data;
		data.m_currency = m_currency;

		if (APawn* pawn = GetPawn())
		{
			data.m_location = pawn->GetActorLocation();
			data.m_components = m_components;
		}

		SaveObject->m_savedPlayer = data;
	}
}
