// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Card.h"
#include "HandHandler.generated.h"

UCLASS()
class KARCIANKA_API AHandHandler : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHandHandler();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		TArray<class ACard*> PlacedCards;

	UFUNCTION(BlueprintCallable)
		void PositionCards();

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Default")
		int stepBase=300;

};
