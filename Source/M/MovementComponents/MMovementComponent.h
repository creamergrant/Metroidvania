// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/MovementComponent.h"
#include "MMovementComponent.generated.h"

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class M_API UMMovementComponent : public UMovementComponent
{
	GENERATED_BODY()
	
public:

	UMMovementComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Move(const FInputActionValue&);
	void Jump();

	void EndCoyoteTime();

protected:

	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jump")
	float m_jumpHeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Jump")
	bool m_bIsAirborne;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Jump|Coyote Time")
	FTimerHandle m_coyoteTimeTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jump|Coyote Time")
	float m_coyoteTimeAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jump|Coyote Time")
	float m_sweepStartOffset;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jump|Coyote Time")
	float m_sweepDistance;

	FCollisionShape m_sweepShape;
	FCollisionQueryParams m_sweepQueryParams;
};
