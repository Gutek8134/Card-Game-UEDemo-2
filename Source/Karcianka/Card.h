// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.generated.h"

UENUM()
enum class EffectType : uint8 {
	healing,
	damaging,
};

USTRUCT()
struct FEffect {
	GENERATED_BODY()

	EffectType type;
};

UCLASS()
class KARCIANKA_API UCard : public UObject
{
	GENERATED_BODY()
	
public:
	FString ToString();

	TArray<FEffect> Effects;
};
