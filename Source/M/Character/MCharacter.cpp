// Fill out your copyright notice in the Description page of Project Settings.


#include "MCharacter.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MMovementComponent.h"
#include "MCombatComponent.h"

// Sets default values
AMCharacter::AMCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_movement = CreateDefaultSubobject<UBoxComponent>("movementComp");
	m_movement->SetSimulatePhysics(true);
	m_movement->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	m_movement->SetCollisionProfileName("BlockAllDynamic");
	m_movement->SetBoxExtent(FVector(100, 10, 100));
	SetRootComponent(m_movement);

	m_mesh = CreateDefaultSubobject<UStaticMeshComponent>("mesh");
	m_mesh->SetSimulatePhysics(false);
	m_mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	m_mesh->SetCollisionProfileName("NoCollision");
	m_mesh->SetupAttachment(RootComponent);

	m_springArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	m_springArm->SetupAttachment(RootComponent);
	m_springArm->SocketOffset = FVector(0, 0, 300);
	m_springArm->SetRelativeRotation(FRotator(0, -90.0f, 0));
	m_springArm->TargetArmLength = 500.0f;
	m_springArm->bEnableCameraLag = true;
	m_springArm->CameraLagSpeed = 30.0f;

	m_camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	m_camera->SetProjectionMode(ECameraProjectionMode::Orthographic);
	m_camera->SetOrthoWidth(5000.0f);
	m_camera->SetupAttachment(m_springArm);
	m_camera->bUsePawnControlRotation = false;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	m_moveComp = CreateDefaultSubobject<UMMovementComponent>("MoveComp");

	m_combatComp = CreateDefaultSubobject<UMCombatComponent>("CombatComp");
}

// Called when the game starts or when spawned
void AMCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AMCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}


