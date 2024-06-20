// Fill out your copyright notice in the Description page of Project Settings.


#include "MEnemyAIControllerBase.h"

AMEnemyAIControllerBase::AMEnemyAIControllerBase()
{
}

void AMEnemyAIControllerBase::OnPossess(APawn* NewPawn)
{
	Super::OnPossess(NewPawn);

	if (m_behaviorTree)
	{
		RunBehaviorTree(m_behaviorTree);
	}
}
