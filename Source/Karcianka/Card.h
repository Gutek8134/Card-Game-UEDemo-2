// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Card.generated.h"

UENUM()
enum class EffectType : uint8 {
	heal,
	attack,
};

UENUM()
enum class EffectTarget : uint8 {
	self, ally, enemy,
};

USTRUCT()
struct FEffect {
	GENERATED_BODY()

	EffectType type;
	
	EffectTarget target;

	int value;
};

FEffect FEffectConstructor(EffectType _type, EffectTarget _target, int _value);


UCLASS()
class KARCIANKA_API UCard : public UObject
{
	GENERATED_BODY()

public:
	UCard();
	UCard(const FString& name, const TArray<FEffect>& effects);

	TArray<FEffect> Effects;

	FString Name = "Some card";

	FString ToString();


protected:
	FString EffectTypeToString(EffectType e);
	FString EffectTargetToString(EffectTarget e);

	const static TArray<FString> EffectTypeStrings;
	const static TArray<FString> EffectTargetStrings;
};
