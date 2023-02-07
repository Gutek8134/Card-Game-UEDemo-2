// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/TextRenderComponent.h"
#include "Card.generated.h"

UENUM(BlueprintType)
enum class EffectType : uint8 {
	heal,
	attack,
};

UENUM(BlueprintType)
enum class EffectTarget : uint8 {
	self, ally, enemy,
};

USTRUCT(BlueprintType)
struct FEffect {
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	EffectType type;
	
	UPROPERTY(BlueprintReadWrite)
	EffectTarget target;

	UPROPERTY(BLueprintReadWrite)
	int value;
};

FEffect FEffectConstructor(EffectType _type, EffectTarget _target, int _value);


UCLASS(Blueprintable)
class KARCIANKA_API ACard : public AActor
{
	GENERATED_BODY()

public:
	ACard();
	ACard(const FString& name, const TArray<FEffect>& effects);

	UFUNCTION(BlueprintCallable)
	void SetValues(const FString& name, const TArray<FEffect>& effects);

	UFUNCTION(BlueprintCallable)
		const TArray<FEffect>& GetEffects();

	UFUNCTION(BlueprintCallable)
		const TArray<EffectTarget> GetPossibleTargets();

	TArray<FEffect> Effects;

	FString Name = "Some card";

	FString ToString();


protected:
	FString EffectTypeToString(EffectType e);
	FString EffectTargetToString(EffectTarget e);

	const static TArray<FString> EffectTypeStrings;
	const static TArray<FString> EffectTargetStrings;

	class UStaticMeshComponent* mesh;
	class UTextRenderComponent* description;
};
