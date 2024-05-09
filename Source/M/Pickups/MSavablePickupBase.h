// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MPickupBase.h"
#include "MSaveObjInterface.h"
#include "MSavablePickupBase.generated.h"

/**
 * 
 */
UCLASS()
class M_API AMSavablePickupBase : public AMPickupBase, public IMSaveObjInterface
{
	GENERATED_BODY()
	
public:

	virtual void OnActorLoaded_Implementation() override;

protected:

	UPROPERTY(SaveGame)
	bool m_bHasBeenPickedUp;
};
