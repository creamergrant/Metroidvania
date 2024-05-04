// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MCharacter.generated.h"

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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Mesh)
	class UMMovementComponent* m_moveComp;

	UPROPERTY(EditAnywhere, Category = Combat)
	class UMCombatComponent* m_combatComp;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
