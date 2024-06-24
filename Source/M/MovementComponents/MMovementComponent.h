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

	void Move(const FVector2D& Value);
	void Jump();
	void JumpEnd();

	void EnableSweepCheck();
	void EndCoyoteTime();

	void CheckAbove();
	void CheckBellow();

	void DropDown();

protected:

	virtual void BeginPlay() override;

	/********************
	* MOVEMENT VARIABLES
	********************/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	FVector2D m_movementValue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement")
	float m_movementSpeed;

	/****************
	* JUMP VARIABLES
	****************/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jump")
	class UCurveFloat* m_jumpCurve;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Jump")
	float m_maxJumpHeight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Jump")
	float m_jumpTimeMax;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Jump")
	float m_jumpTimeCurrent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Jump")
	bool m_bIsJumping;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Jump")
	bool m_bIsAirborne;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Jump|Coyote Time")
	bool m_bDoSweep;

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

	bool m_bCanJump = true;

	class AMCharacter* m_character;

	int m_jumpCount = 0;
};
