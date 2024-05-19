// Fill out your copyright notice in the Description page of Project Settings.


#include "MHorizontalSpell.h"

UMHorizontalSpell::UMHorizontalSpell()
{
}

void UMHorizontalSpell::BeginPlay()
{
}

void UMHorizontalSpell::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
}

void UMHorizontalSpell::OnRegister()
{
}

void UMHorizontalSpell::FireSpell()
{
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Blue, "fire spell");
}
