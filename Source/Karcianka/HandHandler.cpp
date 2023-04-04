// Fill out your copyright notice in the Description page of Project Settings.


#include "HandHandler.h"

// Sets default values
AHandHandler::AHandHandler()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void AHandHandler::TogglePlacedCardsVisibility() {
	bSpawnCardsHidden = !bSpawnCardsHidden;
	for (const auto& el : PlacedCards) {
		el->SetActorHiddenInGame(bSpawnCardsHidden);
	}
}

void AHandHandler::PositionCards() {
	TArray<float> newPositions;
	newPositions.Init(0, PlacedCards.Num());
	float position, step = stepBase * GetActorScale().Y;

	if (PlacedCards.Num() % 2 == 0) {
		position = -stepBase / 2 * (PlacedCards.Num()-1) * GetActorScale().Y;
	}
	else
	{
		position = -stepBase / 2 * PlacedCards.Num() * GetActorScale().Y + stepBase/2;
	}

	for (auto i = 0; i < PlacedCards.Num(); ++i) {
		newPositions[i] = position;
		position += step;
	}

	for (auto i = 0; i < PlacedCards.Num(); ++i) {
		PlacedCards[i]->SetActorLocation(GetActorLocation() + FVector(newPositions[i], 0, 0));
	}
}

TMap<TSubclassOf<ACard>, uint8> AHandHandler::GetCardsToSpawn(TMap<TSubclassOf<ACard>, uint8> hand) {
	for (const auto& el : PlacedCards)
		hand[el->GetClass()] -= 1;
	return hand;
}