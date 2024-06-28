// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MCharacter.generated.h"

UENUM()
enum class AnimState
{
	Idle,
	Walk,
	Jump,
	Dash,
	Attack
};

UCLASS()
class M_API AMCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMCharacter();

	UPROPERTY(EditAnywhere, Category = Temp)
	class UStaticMeshComponent* m_mesh;

	UPROPERTY(EditAnywhere, Category = HitBox)
	class UBoxComponent* m_movement;

	UPROPERTY(EditAnywhere, Category = Camera)
	class USpringArmComponent* m_springArm;

	UPROPERTY(EditAnywhere, Category = Camera)
	class UCameraComponent* m_camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class UMMovementComponent* m_moveComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Movement)
	class UMDashComponent* m_dashComp;

	UPROPERTY(EditAnywhere, Category = Combat)
	class UMCombatComponent* m_combatComp;

	UPROPERTY(EditAnywhere, Category = Combat)
	TMap<FString, class UMSpellComponent*> m_spells;

	UPROPERTY(EditAnywhere, Category = Movement)
	TMap<FString, USceneComponent*> m_movementComps;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	class UMAnimationComponent* m_aniComp;

	FRotator GetSpellDirection();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	int m_mana = 0;
	int m_health = 100;
	int m_maxHealth = 100;

	const int m_maxMana = 99;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	float m_movementStat;
	float m_dmgStat;
	float m_healthStat;
	float m_weightStat;
	float m_strengthStat;
	float m_atkSpeedStat;

	UPROPERTY(SaveGame)
	TArray<class UMEquipable*> m_equips;

	void IncreaseStats();

	FVector2D GetMovementValue();
	bool GetIsAirborne();
	bool GetIsJumping();
	bool GetIsDashing();
	bool GetIsAttacking();

	void SetCanAttack(bool canAttack);

	int GetMana() { return m_mana; }
	void IncreaseMana(int add);
	void SetMana(int mana);
	void DecreaseMana(int sub);
	int GetHealth() { return m_health; }
	void IncreaseHealth(int add);
	void SetHealth(int health);
	void DecreaseHealth(int sub);
};
