// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MOneWayPlatform.generated.h"

UCLASS()
class M_API AMOneWayPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMOneWayPlatform();

	UPROPERTY(EditAnywhere, Category = HitBox)
	class UBoxComponent* m_hitBox;

	UPROPERTY(EditAnywhere, Category = Mesh)
	UStaticMeshComponent* m_mesh;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
