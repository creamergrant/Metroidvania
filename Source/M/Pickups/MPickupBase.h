// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MPickupBase.generated.h"

UCLASS()
class M_API AMPickupBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMPickupBase();

	UPROPERTY(EditAnywhere, Category = HitBox)
	class UBoxComponent* m_collision;

	UPROPERTY(EditAnywhere, Category = HitBox)
	class UPaperSpriteComponent* m_sprite;

	virtual void OnPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void OnComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
