// Fill out your copyright notice in the Description page of Project Settings.


#include "Card.h"

FEffect FEffectConstructor(EffectType _type, EffectTarget _target, int _value)
{
	FEffect temp;
	temp.type = _type;
	temp.target = _target;
	temp.value = _value;
	return temp;
}

UCard::UCard() {
}

UCard::UCard(const FString& name, const TArray<FEffect>& effects) {
	this->Name = name;
	this->Effects = effects;
}

void UCard::SetValues(const FString& name, const TArray<FEffect>& effects) {
	this->Name = name;
	this->Effects = effects;
}

const TArray<FString> UCard::EffectTypeStrings = { "Heal", "Attack" };
const TArray<FString> UCard::EffectTargetStrings = { "Self", "Ally", "Enemy" };

FString UCard::EffectTypeToString(EffectType e) {
	return UCard::EffectTypeStrings[(uint8)e];
}

FString UCard::EffectTargetToString(EffectTarget e) {
	return UCard::EffectTargetStrings[(uint8)e];
}

FString UCard::ToString() {
	FString temp = this->Name + ":\n";
	for (auto const& e : this->Effects) {
		temp += EffectTypeToString(e.type) + TEXT(" ") + EffectTargetToString(e.target) + TEXT(" ") + FString::FromInt(e.value) + "\n";
	}
	return temp;
}