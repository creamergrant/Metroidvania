// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MProjectile.h"
#include "MAcceleratingSpellProjectile.generated.h"

/**
 *
 */
UCLASS()
class M_API AMAcceleratingSpellProjectile : public AMProjectile
{
	GENERATED_BODY()

public:
	AMAcceleratingSpellProjectile();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* m_mesh;

	UPROPERTY(EditDefaultsOnly, Category = HitBox)
	class UBoxComponent* m_explosionHitBox;

protected:
	virtual void BeginPlay() override;
	void Accelerate();
	void Explode();

	float lifetimeTimer = 0.0f;
	float maxLifetime = 1.0f;

	TArray<AActor*> overlappingActors;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* Other,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;
};
