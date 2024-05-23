// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MSpellComponent.h"
#include "MProjectile.h"
#include "MHorizontalSpell.generated.h"

/**
 * 
 */
UCLASS()
class M_API UMHorizontalSpell : public UMSpellComponent
{
	GENERATED_BODY()
	
public:
	UMHorizontalSpell();

	TSubclassOf<AMProjectile> m_projectile;

	class UStaticMesh* m_mesh;
protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void OnRegister() override;

	virtual void FireSpell();
};
