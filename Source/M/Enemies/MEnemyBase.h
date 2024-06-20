// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "MEnemyBase.generated.h"

/**
 * 
 */
UCLASS()
class M_API AMEnemyBase : public APaperCharacter
{
	GENERATED_BODY()
	
public:
	
	AMEnemyBase();

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable) //Blueprint callable to be set in a behavior tree task.
	void SetIsWalking(bool bIsWalking);

	UFUNCTION(BlueprintCallable) //Blueprint callable to checked in behavior tree decorator.
	bool GetIsWalking();

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void ComponentOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void ComponentOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Detector")
	class UBoxComponent* m_ledgeDetector;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Detector")
	class UBoxComponent* m_wallDetector;

	/**********************
	* AI WALKING VARIABLES
	**********************/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Walking")
	bool m_bIsWalking;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Walking")
	FVector m_direction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI Walking")
	float m_walkSpeed;
};
