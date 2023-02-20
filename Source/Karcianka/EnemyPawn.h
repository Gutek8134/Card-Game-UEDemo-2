// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ACardPawn.h"
#include <random>
#include "Components/WidgetComponent.h"
#include "EnemyPawn.generated.h"

UCLASS()
class KARCIANKA_API AEnemyPawn : public ACardPawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AEnemyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void AutoHeal() override;

	virtual void AutoAttack() override;

	virtual void ReceiveDamage(const uint8& damage) override;

};