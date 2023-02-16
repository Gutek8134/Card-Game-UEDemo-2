// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"

ACard::ACard() {
	root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	description = CreateDefaultSubobject<UTextRenderComponent>(TEXT("Description"));
	description->Text = FText::FromString("Card name:\nLorem Ipsum Something Effect 10");
	RootComponent = root;
	mesh->SetupAttachment(RootComponent);
	description->SetupAttachment(mesh);
}

ACard::ACard(const FString& name, const TArray<FEffect>& effects) {
	this->Name = name;
	this->Effects = effects;
}

void ACard::SetValues(const FString& name, const TArray<FEffect>& effects) {
	this->Name = name;
	this->Effects = effects;
	description->Text = FText::FromString(this->ToString());
}

const TArray<FString> ACard::EffectTypeStrings = { "Heal", "Attack" };
const TArray<FString> ACard::EffectTargetStrings = { "Self", "Ally", "Enemy" };

FString ACard::EffectTypeToString(EffectType e) {
	return ACard::EffectTypeStrings[(uint8)e];
}

FString ACard::EffectTargetToString(EffectTarget e) {
	return ACard::EffectTargetStrings[(uint8)e];
}

const TArray<FEffect>& ACard::GetEffects() {
	return this->Effects;
}

const TArray<EffectTarget> ACard::GetPossibleTargets() {
	TArray<EffectTarget> t;
	for (const auto& e : this->Effects) {
		t.AddUnique(e.target);
	}
	return t;
}

bool ACard::IsOfType(EffectType type) {
	for (const auto& effect : this->Effects)
		if (effect.type == type)
			return true;
	return false;
}

bool ACard::CanBeUsedOn(EffectTarget target) {
	for (const auto& effect : this->Effects)
		if (effect.target == target)
			return true;
	return false;
}

int ACard::GetSumaricEffects(EffectType type) {
	int t = 0;
	for (const auto& effect : this->Effects) {
		if (effect.type == type)
			t += effect.value;
	}
	return t;
}

FString ACard::ToString() {
	FString temp = this->Name + ":\n";
	TArray<TPair<FEffect, uint8>> count;

	FEffect previous = Effects[0];
	auto number = 0;
	for (const auto& effect : Effects) {
		if (effect != previous) {
			temp += EffectTypeToString(previous.type) + TEXT(" ") + EffectTargetToString(previous.target) + TEXT(" ") + (number == 1 ? "" : (FString::FromInt(previous.value) + " X " + FString::FromInt(number))) + "\n";
			number = 0;
		}
		number++;
		previous = effect;
	}
	temp += EffectTypeToString(previous.type) + TEXT(" ") + EffectTargetToString(previous.target) + TEXT(" ") + FString::FromInt(previous.value) + " X " + FString::FromInt(number) + "\n";
	return temp;
}