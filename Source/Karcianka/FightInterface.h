// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "FightInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, NotBlueprintable)
class UFight : public UInterface
{
	GENERATED_BODY()
};

/**
 *
 */
class KARCIANKA_API IFight
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable)
		virtual void ReceiveDamage(const uint8& damage) = 0;
	UFUNCTION(BlueprintCallable)
		virtual void Heal(const uint8& value) = 0;
	UFUNCTION(BlueprintCallable)
		virtual void GainAP(const uint8& value) = 0;
};
