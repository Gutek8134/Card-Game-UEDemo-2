// Copyright Epic Games, Inc. All Rights Reserved.


#include "KarciankaGameModeBase.h"

void AKarciankaGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) {
	auto t = NewObject<ACard>();
	t->SetValues("New Card", { FEffect(EffectType::attack, EffectTarget::enemy, 15), FEffect(EffectType::heal, EffectTarget::ally, 5) });
	UE_LOG(LogTemp, Warning, TEXT("%s"), *t->ToString());
	Super::InitGame(MapName, Options, ErrorMessage);
}