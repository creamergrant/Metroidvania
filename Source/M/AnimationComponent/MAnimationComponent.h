// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "MAnimationComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class M_API UMAnimationComponent : public USceneComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMAnimationComponent();


	UPROPERTY(EditAnywhere, Category = Sprite)
	class UPaperFlipbookComponent* m_sprite;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FlipBooks)
	class UPaperFlipbook* m_idleAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FlipBooks)
	class UPaperFlipbook* m_dashAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FlipBooks)
	class UPaperFlipbook* m_jumpAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FlipBooks)
	class UPaperFlipbook* m_fallingAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FlipBooks)
	class UPaperFlipbook* m_walkAnim;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FlipBooks)
	class UPaperFlipbook* m_groundAtk1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FlipBooks)
	class UPaperFlipbook* m_groundAtk2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = FlipBooks)
	class UPaperFlipbook* m_groundAtk3;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnRegister() override;

	class AMCharacter* m_character;

	void UpdateAnimation();

	bool m_attackAnimation = false;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SwapAnimation(class UPaperFlipbook* anim, bool looping = true);

	UFUNCTION()
	void OnFinshedPlaying();

	void IncreaseMana(int add);
};
