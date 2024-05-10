// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MSaveObjInterface.h"
#include "MInteractInterface.h"
#include "MInteractBase.generated.h"

UCLASS()
class M_API AMInteractBase : public AActor, public IMSaveObjInterface, public IMInteractInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMInteractBase();

	virtual void OnActorLoaded();

	virtual void OnInteract();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
