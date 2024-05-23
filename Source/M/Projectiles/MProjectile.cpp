// Fill out your copyright notice in the Description page of Project Settings.


#include "MProjectile.h"

// Sets default values
AMProjectile::AMProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

