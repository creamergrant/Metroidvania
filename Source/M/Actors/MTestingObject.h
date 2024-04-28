// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MSaveObjInterface.h"
#include "MTestingObject.generated.h"

UCLASS()
class M_API AMTestingObject : public AActor, public IMSaveObjInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMTestingObject();

	UPROPERTY(SaveGame)
	bool m_open = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* m_mesh;

	virtual void OnActorLoaded_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ToggleOpen();

};
