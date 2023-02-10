// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyPawn.h"
#include "PlayerPawn.generated.h"

UCLASS()
class KARCIANKA_API APlayerPawn : public ACardPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	APlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Heal();

	virtual void Attack();

	virtual void ReceiveDamage(const uint8& damage) override;

protected:
	class UStaticMeshComponent* mesh;
};
