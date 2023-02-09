// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Card.h"
#include "MyPlayerState.h"
#include "FightInterface.h"
#include "EnemyPawn.generated.h"

UCLASS()
class KARCIANKA_API AEnemyPawn : public APawn, public IFight
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

	UFUNCTION(BlueprintCallable)
		const TMap<TSubclassOf<ACard>, uint8>& GetDeck();
	UFUNCTION(BlueprintCallable)
		const TMap<TSubclassOf<ACard>, uint8>& GetHand();

	UFUNCTION(BlueprintCallable)
		bool HasCardOfType(EffectType type);

	UFUNCTION(BlueprintCallable)
		void Heal();

	UFUNCTION(BlueprintCallable)
		void Attack();

	UFUNCTION(BlueprintCallable)
		int GetHP();

	UFUNCTION(BlueprintCallable)
		int GetMaxHP();

	UFUNCTION(BlueprintCallable)
		virtual void ReceiveDamage(const uint8& damage) override;

protected:
	//Holds type and number of cards in deck and current hand
	UPROPERTY(EditAnywhere, Category = "Playstyle")
		TMap<TSubclassOf<ACard>, uint8> Deck;
	UPROPERTY(VisibleAnywhere, Category = "Playstyle")
		TMap<TSubclassOf<ACard>, uint8> Hand;

	UPROPERTY(EditAnywhere, Category = "Playstyle")
		uint8 HandSize;
	class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = "Stats")
		int hp;
	UPROPERTY(EditAnywhere, Category = "Stats")
		int maxHP;
};
