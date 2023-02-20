// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerPawn.h"

// Sets default values
APlayerPawn::APlayerPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	RootComponent = mesh;
	canvas = CreateDefaultSubobject<UWidgetComponent>(TEXT("canvas"));
	canvas->SetupAttachment(mesh);
	canvas->SetWidgetSpace(EWidgetSpace::Screen);
}

// Called when the game starts or when spawned
void APlayerPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerPawn::Heal(const uint8& value) {
	hp += value;
	if (hp > maxHP)
		hp = maxHP;
	UpdateHealthBar();
}

void APlayerPawn::ReceiveDamage(const uint8& damage) {
	hp -= damage;
	if (hp <= 0)
		Die.ExecuteIfBound();
	UpdateHealthBar();
}