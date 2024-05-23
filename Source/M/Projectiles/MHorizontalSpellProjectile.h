// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MProjectile.h"
#include "MHorizontalSpellProjectile.generated.h"

/**
 * 
 */
UCLASS()
class M_API AMHorizontalSpellProjectile : public AMProjectile
{
	GENERATED_BODY()
	
public:
	AMHorizontalSpellProjectile();

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* m_mesh;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComp,
		AActor* Other,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) override;
};
