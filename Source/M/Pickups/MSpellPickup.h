// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MPickupBase.h"
#include "MSpellPickup.generated.h"

/**
 * 
 */
UCLASS()
class M_API AMSpellPickup : public AMPickupBase
{
	GENERATED_BODY()
	
public:

	AMSpellPickup();

	UPROPERTY(EditAnywhere, Category = Pickup)
	TSubclassOf<class UMSpellComponent> ComponentClass;

	virtual void OnPickup();

protected:
	virtual void BeginPlay() override;

	virtual void OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	virtual void Tick(float DeltaTime) override;
};
