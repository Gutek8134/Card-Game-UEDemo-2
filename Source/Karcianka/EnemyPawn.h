// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Card.h"
#include "MyPlayerState.h"
#include "FightInterface.h"
#include "EnemyPawn.generated.h"

//Base, theoretically abstract, class for pawns using cards
UCLASS(MinimalAPI, NotBlueprintable)
class ACardPawn : public APawn, public IFight {
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
		const TMap<TSubclassOf<ACard>, uint8>& GetDeck();
	UFUNCTION(BlueprintCallable)
		const TMap<TSubclassOf<ACard>, uint8>& GetHand();

	UFUNCTION(BlueprintCallable)
		bool HasCardOfType(EffectType type);

	//Overriden from IFight, used to receive outside healing
	virtual void Heal(const uint8& value) override;

	//Overriden from IFight, used to receive outside damage
	virtual void ReceiveDamage(const uint8& damage) override;

	//Automatic self-targeted heal
	UFUNCTION(BlueprintCallable)
		virtual void AutoHeal();

	//Automatic player-targeted attack
	UFUNCTION(BlueprintCallable)
		virtual void AutoAttack();

	UFUNCTION(BlueprintCallable)
		void Play(ACard* card, ACardPawn* target);

	UFUNCTION(BlueprintCallable)
		int GetHP();

	UFUNCTION(BlueprintCallable)
		int GetMaxHP();

	//Used for updating HUD's health bar
	UFUNCTION(BlueprintCallable)
		virtual void UpdateHealthBar();

protected:
	UPROPERTY(EditAnywhere, Category = "Stats")
		int hp;
	UPROPERTY(EditAnywhere, Category = "Stats")
		int maxHP;
	//A list of statuses currently affecting entity
	UPROPERTY(VisibleAnywhere, Category = "Stats")
		TMap<FEffect, int> statuses;

	//Holds type and number of cards in deck
	UPROPERTY(EditAnywhere, Category = "Playstyle")
		TMap<TSubclassOf<ACard>, uint8> Deck;
	//Holds type and number of cards in current hand
	UPROPERTY(VisibleAnywhere, Category = "Playstyle")
		TMap<TSubclassOf<ACard>, uint8> Hand;

	UPROPERTY(EditAnywhere, Category = "Playstyle")
		uint8 HandSize;
};

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

	virtual void UpdateHealthBar() override;

protected:
	class UStaticMeshComponent* mesh;
};