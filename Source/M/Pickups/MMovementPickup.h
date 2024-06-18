// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MPickupBase.h"
#include "MMovementPickup.generated.h"

/**
 * 
 */
UCLASS()
class M_API AMMovementPickup : public AMPickupBase
{
	GENERATED_BODY()

public:
	AMMovementPickup();

	UPROPERTY(EditAnywhere, Category = MovementComponent)
	TSubclassOf<USceneComponent> m_component;

	virtual void OnPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
