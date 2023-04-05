// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "FightInterface.h"
#include "Card.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "MyPlayerState.h"
#include "ACardPawn.generated.h"

//Base, theoretically abstract, class for pawns using cards
UCLASS(MinimalAPI, NotBlueprintable)
class ACardPawn : public APawn, public IFight {
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		bool HasCardOfType(EffectType type);

	//Overriden from IFight, used to receive outside healing
	virtual void Heal(const uint8& value) override;

	//Overriden from IFight, used to receive outside damage
	virtual void ReceiveDamage(const uint8& damage) override;

	virtual void GainAP(const uint8& value) override;

	//Automatic self-targeted heal
	UFUNCTION(BlueprintCallable)
		virtual void AutoHeal();

	//Automatic player-targeted attack
	UFUNCTION(BlueprintCallable)
		virtual void AutoAttack();

	UFUNCTION(BlueprintCallable)
		virtual void Play(ACard* card, ACardPawn* cardTarget);

	UFUNCTION(BlueprintCallable)
		int GetHP();

	UFUNCTION(BlueprintCallable)
		int GetMaxHP();

	//Used for updating HUD's health bar
	UFUNCTION(BlueprintCallable)
		void UpdateHealthBar();

	UFUNCTION(BlueprintCallable)
		UProgressBar* GetProgressBar();

	UFUNCTION(BlueprintCallable)
		void SetProgressBar(UProgressBar* progressBar);

	UFUNCTION(BlueprintCallable)
		void StartFight();

	UFUNCTION(BlueprintCallable)
		virtual void StartTurn();

	UFUNCTION(BlueprintCallable)
		void EndTurn();

	UPROPERTY(BlueprintReadWrite, Category = "Playstyle")
		bool bTurnEnded;

	UFUNCTION(BlueprintCallable)
		void DrawCards(uint8 number);

	UFUNCTION(BlueprintCallable)
		void DiscardCards(ACard* card, uint8 number);

	UFUNCTION(BlueprintCallable)
		void DiscardCardsOfClass(TSubclassOf<ACard> cardType, uint8 number);

	UFUNCTION(BlueprintCallable)
		bool EnoughAPToPlay(ACard* card);


protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int hp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stats")
		int maxHP;
	//A list of statuses currently affecting entity
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Stats")
		TMap<FEffect, int> statuses;

	//Holds type and number of cards in deck
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playstyle")
		TMap<TSubclassOf<ACard>, uint8> Deck;

	//Holds the current stack of cards from which player can draw
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Playstyle")
		TMap<TSubclassOf<ACard>, uint8> Stack;

	//Holds type and number of cards in current hand
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Playstyle")
		TMap<TSubclassOf<ACard>, uint8> Hand;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playstyle")
		uint8 HandSize = 5;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Playstyle")
		uint8 DrawnCards = 1;

	UPROPERTY(BlueprintReadOnly, Category = "Playstyle")
		int32 StackWeight;

	UPROPERTY(BlueprintReadOnly, Category = "Playstyle")
		int32 HandWeight;

	UPROPERTY(EditAnywhere, Category = "Graphics")
		class UStaticMeshComponent* mesh;

	UPROPERTY(EditAnywhere, Category = "Graphics")
		class UWidgetComponent* canvas;

	UPROPERTY(EditAnywhere, Category = "Graphics")
		class UProgressBar* ProgressBar;

	UPROPERTY(BlueprintReadWrite, Category = "Graphics")
		class UTextBlock* HPText;

	UPROPERTY(BlueprintReadwrite)
		bool bInFight;

	UPROPERTY(EditAnywhere, Category = "Playstyle")
		uint8 APstarting;

	UPROPERTY(EditAnywhere, Category = "Playstyle")
		uint8 APgain;

	UPROPERTY(BlueprintReadWrite, Category = "Playstyle")
		uint8 APcurrent;

	UFUNCTION(BlueprintNativeEvent)
		void IndicateNoAP(ACard* ExpansiveCard);
};