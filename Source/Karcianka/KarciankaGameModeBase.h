// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <stdexcept>
#include "CoreMinimal.h"
#include "Card.h"
#include "GameFramework/GameModeBase.h"
#include "KarciankaGameModeBase.generated.h"

/**
 *
 */
UCLASS()
class KARCIANKA_API AKarciankaGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

protected:
	//Weighed list card: chance to get
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		TMap<TSubclassOf<ACard>, uint8> ObtainableCards;

	UFUNCTION(BlueprintCallable)
		TArray<TSubclassOf<ACard>> FGenerateRandomObtainableCards(uint8 number);
	UFUNCTION(BlueprintCallable)
		void GenerateRandomObtainableCards(TArray<TSubclassOf<ACard>>& temp, uint8 number);
	
	uint16 GetObtainableCardsWeight();
};
