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

	UPROPERTY(EditDefaultsOnly, Category = UpAttack)
	UBoxComponent* m_upAtk;
	UPROPERTY(EditDefaultsOnly, Category = DownAttack)
	UBoxComponent* m_downAtk;

	bool m_attack = false;

	enum class AttackType m_attackType;

	ComboStep m_comboStep = ComboStep::NoAttack;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

	void ResetAttack();

	FTimerHandle m_resetAttack;

	UBoxComponent* m_currentHitBox;

	UBoxComponent* SelectHitBox();

	class UMAnimationComponent* m_aniComp;

	int m_impactFrameNum = 3;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Attack();

	bool m_bIsAttacking = false;
	bool m_canAttack = true;

	bool GetIsAttacking() { return m_bIsAttacking; }

	ComboStep GetComboStep() { return m_comboStep; }

	void SetAttackType(enum class AttackType type) { m_attackType = type; }

	enum class AttackType GetAttackType() { return m_attackType; }

	FName GetActiveHitBoxName();
};
