// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSpellComponent.h"
#include "MProjectile.h"
#include "MAcceleratingSpell.generated.h"

/**
 *
 */
UCLASS()
class M_API UMAcceleratingSpell : public UMSpellComponent
{
	GENERATED_BODY()

public:
	UMAcceleratingSpell();

	TSubclassOf<AMProjectile> m_projectile;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnRegister() override;

	virtual void FireSpell();
};
