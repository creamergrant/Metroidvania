// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MEquipable.generated.h"

UENUM(BlueprintType)
enum class StatType
{
	NoIncrease,
	Movement,
	Damage,
	Health,
	Weight,
	Strength,
	AttackSpeed
};

USTRUCT()
struct FStat
{
	GENERATED_BODY()
	StatType m_type;
	float m_increaseAmt;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class M_API UMEquipable : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMEquipable();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	TArray<FStat*> m_stats;

	virtual void EventTrigger();
};
