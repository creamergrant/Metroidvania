// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MEnemyAIControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class M_API AMEnemyAIControllerBase : public AAIController
{
	GENERATED_BODY()

public:
	AMEnemyAIControllerBase();
	
	virtual void OnPossess(APawn* NewPawn) override;

protected:

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> m_behaviorTree;
};
