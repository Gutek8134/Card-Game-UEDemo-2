// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Components/TextRenderComponent.h"
#include "FEffect.h"
#include "Card.generated.h"

//Base class to be blueprinted into specific cards
UCLASS(Blueprintable)
class KARCIANKA_API ACard : public AActor
{
	GENERATED_BODY()

public:
	ACard();
	ACard(const FString& name, const TArray<FEffect>& effects);

	UFUNCTION(BlueprintCallable)
		void SetValues(const FString& name, const TArray<FEffect>& effects);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void SetValuesOnDefault();

	UFUNCTION(BlueprintCallable)
		const TArray<FEffect>& GetEffects();

	UFUNCTION(BlueprintCallable)
		const TArray<EffectTarget> GetPossibleTargets();

	UFUNCTION(BlueprintCallable)
		bool IsOfType(EffectType type);

	UFUNCTION(BlueprintCallable)
		bool CanBeUsedOn(EffectTarget target);

	UFUNCTION(BlueprintCallable)
		int GetSumaricEffects(EffectType type);

	FString Name = "Some card";

	//Auto-description
	UFUNCTION(BlueprintCallable)
		FString ToString();

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		uint8 APcost = 1;

protected:
	//Effects the card applies when played
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
		TArray<FEffect> Effects;
	FString EffectTypeToString(EffectType e);
	FString EffectTargetToString(EffectTarget e);

	const static TArray<FString> EffectTypeStrings;
	const static TArray<FString> EffectTargetStrings;

	UPROPERTY(EditAnywhere, Category = "Graphics")
		class USceneComponent* root;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Graphics")
		class UStaticMeshComponent* mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Graphics")
		class UTextRenderComponent* description;
};

ACard* GetDefaultCard(TSubclassOf<ACard>);