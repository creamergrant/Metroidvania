// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "MDashComponent.generated.h"

/**
 * 
 */
UCLASS()
class M_API UMDashComponent : public UMovementComponent
{
	GENERATED_BODY()
	
public:
	UMDashComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Dash();
	virtual void EndDash();

	virtual void EnableCanDash();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dash")
	bool m_bCanDash;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dash")
	bool m_bIsDashing;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dash")
	float m_dashDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dash")
	FTimerHandle m_dashDurationTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dash")
	float m_dashDurationTimeAmount;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Dash")
	FTimerHandle m_dashCooldownTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dash")
	float m_dashCooldownTimeAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Dash")
	float m_dashImpulseValue;
};
