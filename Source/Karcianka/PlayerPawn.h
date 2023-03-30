// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyPawn.h"
#include "Card.h"
#include "PlayerPawn.generated.h"

UCLASS(Blueprintable)
class KARCIANKA_API APlayerPawn : public ACardPawn
{
	GENERATED_BODY()

		DECLARE_DELEGATE(VoidDelegate)
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

	virtual void Heal(const uint8& value) override;

	UFUNCTION(BlueprintCallable)
		virtual void ReceiveDamage(const uint8& damage) override;

	virtual void GainAP(const uint8& value) override;

	void Play(ACard* card, ACardPawn* cardTarget) override;
	void StartTurn() override;

	UFUNCTION(BlueprintCallable)
		void UpdateAPText();

	UFUNCTION(BlueprintNativeEvent)
	void Die();

protected:
	UPROPERTY(BlueprintReadWrite)
		UTextBlock* APText;
};
