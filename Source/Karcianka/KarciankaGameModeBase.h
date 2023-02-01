// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

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
};
