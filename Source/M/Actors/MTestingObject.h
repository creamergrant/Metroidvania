// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MInteractBase.h"
#include "MTestingObject.generated.h"

UCLASS()
class M_API AMTestingObject : public AMInteractBase
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMTestingObject();

	UPROPERTY(SaveGame)
	bool m_open = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
	class UStaticMeshComponent* m_mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
	class UMMovementComponent* m_moveComp;

	UPROPERTY(SaveGame)
	FLinearColor m_color;

	virtual void OnActorLoaded_Implementation() override;

	virtual void OnInteract_Implementation() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ToggleOpen();

};
