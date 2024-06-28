// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class M_API AMPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* m_mappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_toggleOpenAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_saveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_interactAction;
  
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_moveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_jumpAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_dashAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_attackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* m_spellAction;


	virtual void SetupInputComponent() override;
	virtual void AcknowledgePossession(APawn* PossesedPawn) override;
	virtual void BeginPlay() override;

	void ToggleOpen();
	void Interact();

	void Save();

	void Attack();

	void Move(const FInputActionValue& Value);
	void Jump();
	void JumpEnd();
	void Dash();
	void Spell();

	bool m_canSpell = true;

	void CanSpell();

	FVector2D m_currentDirectionalInput;
	FVector2D m_lastDirectionalInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Input)
	bool m_bAreMovementControlsLocked = false; //pardon the Jimmy-ism

public:
	class AMCharacter* m_character;

	FVector2D GetCurrentDirectionalInput() const { return m_currentDirectionalInput; }
	FVector2D GetLastDirectionalInput() const { return m_lastDirectionalInput; }

	void SetMovementControlLockState(bool State);
};
