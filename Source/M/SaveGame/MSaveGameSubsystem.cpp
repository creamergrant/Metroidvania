// Fill out your copyright notice in the Description page of Project Settings.


#include "MSaveGameSubsystem.h"
#include "MSaveSettings.h"
#include "MPlayerState.h"
#include "MSaveGame.h"
#include "MSaveObjInterface.h"
#include "MGameStateBase.h"

#include "EngineUtils.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
#include "Kismet/GameplayStatics.h"

void UMSaveGameSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	const UMSaveSettings* saveSettings = GetDefault<UMSaveSettings>();

	m_currentSlotName = saveSettings->m_saveSlotName;

	UDataTable* dummyTable = saveSettings->m_dummyTablePath.LoadSynchronous();
}

void UMSaveGameSubsystem::HandlePlayer(AController* NewPlayer)
{
	AMPlayerState* ps = NewPlayer->GetPlayerState<AMPlayerState>();
	if (ps)
	{
		ps->LoadPlayerState(m_currentSaveGame);
	}
}

bool UMSaveGameSubsystem::OverrideSpawnTransform(AController* NewPlayer)
{
	if (!NewPlayer) return false;

	AMPlayerState* ps = NewPlayer->GetPlayerState<AMPlayerState>();
	if (!ps) return false;
	
	if (APawn* pawn = ps->GetPawn())
	{
		FPlayerSaveData* data = m_currentSaveGame->GetPlayerData();
	
		if (data)
		{
			pawn->SetActorLocation(data->m_location);
	
			return true;
		}
	}

	return false;
}

void UMSaveGameSubsystem::SetSlotName(FString slotname)
{
	if (slotname.Len() == 0)return;

	m_currentSlotName = slotname;
}

void UMSaveGameSubsystem::WriteSaveGame()
{
	FPlayerSaveData data;
	m_currentSaveGame->m_savedPlayer = data;
	m_currentSaveGame->m_savedActors.Empty();
	
	AMGameStateBase* gs = Cast<AMGameStateBase>(GetWorld()->GetGameState());
	if (!gs) return;
	
	AMPlayerState* ps = Cast<AMPlayerState>(gs->PlayerArray[0]);
	ps->SavePlayerState(m_currentSaveGame);
	
	for (FActorIterator It(GetWorld()); It; ++It)
	{
		AActor* actor = *It;
	
		if (!actor || actor->Implements<UMSaveObjInterface>())
			continue;
	
		FActorSaveData actorData;
		actorData.m_transform = actor->GetActorTransform();
		actorData.m_name = actor->GetFName();
	
		FMemoryWriter memWriter(actorData.m_byteData);
	
		FObjectAndNameAsStringProxyArchive ar(memWriter, true);
		ar.ArIsSaveGame = true;
	
		actor->Serialize(ar);
	
		m_currentSaveGame->m_savedActors.Add(actorData);
	}
	
	UGameplayStatics::SaveGameToSlot(m_currentSaveGame, m_currentSlotName, 0);
	
	OnSaveGameWritten.Broadcast(m_currentSaveGame);
}

void UMSaveGameSubsystem::LoadSaveGame(FString InSlotName)
{
	SetSlotName(InSlotName);

	if (UGameplayStatics::DoesSaveGameExist(m_currentSlotName, 0))
	{
		m_currentSaveGame = Cast<UMSaveGame>(UGameplayStatics::LoadGameFromSlot(m_currentSlotName, 0));
	
		if (!m_currentSaveGame)
		{
			return;
		}
	
		for (FActorIterator It(GetWorld()); It; ++It)
		{
			AActor* actor = *It;
			if (!actor->Implements<UMSaveObjInterface>())
				continue;
	
			for (FActorSaveData data : m_currentSaveGame->m_savedActors)
			{
				if (data.m_name == actor->GetFName())
				{
					actor->SetActorTransform(data.m_transform);
	
					FMemoryReader memReader(data.m_byteData);
	
					FObjectAndNameAsStringProxyArchive ar(memReader, true);
	
					ar.ArIsSaveGame = true;
	
					actor->Serialize(ar);
	
					IMSaveObjInterface::Execute_OnActorLoaded(actor);
	
					break;
				}
			}
		}
	
		OnSaveGameLoaded.Broadcast(m_currentSaveGame);
	}
	else
	{
		m_currentSaveGame = Cast<UMSaveGame>(UGameplayStatics::CreateSaveGameObject(UMSaveGame::StaticClass()));
	}
}