// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class KARCIANKA_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		int GetHP();

	UFUNCTION(BlueprintCallable)
		void SetHP(int hp);

protected:
	UPROPERTY(EditDefaultsOnly)
	int HP=100;
};
