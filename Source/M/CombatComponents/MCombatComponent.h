// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MCombatComponent.generated.h"

class UBoxComponent;

UENUM()
enum class ComboStep
{
	NoAttack,
	Start,
	Middle,
	Last
};

UENUM()
enum class AttackType
{
	Ground,
	Air,
	Up,
	Down
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class M_API UMCombatComponent : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMCombatComponent();

	UPROPERTY(EditDefaultsOnly, Category = GroundAttacks)
	UBoxComponent* m_groundAtk1;
	UPROPERTY(EditDefaultsOnly, Category = GroundAttacks)
	UBoxComponent* m_groundAtk2;
	UPROPERTY(EditDefaultsOnly, Category = GroundAttacks)
	UBoxComponent* m_groundAtk3;

	bool m_attack = false;

	AttackType m_attackType;

	ComboStep m_comboStep = ComboStep::NoAttack;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void ResetAttack();

	FTimerHandle m_resetAttack;

	UBoxComponent* m_currentHitBox;

	UBoxComponent* SelectHitBox();



public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Attack();
};
