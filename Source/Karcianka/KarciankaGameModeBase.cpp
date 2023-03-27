// Copyright Epic Games, Inc. All Rights Reserved.


#include "KarciankaGameModeBase.h"

void AKarciankaGameModeBase::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) {
	Super::InitGame(MapName, Options, ErrorMessage);
}

TArray<TSubclassOf<ACard>> AKarciankaGameModeBase::FGenerateRandomObtainableCards(uint8 number) {
	// Number must be lesser or equal than the number of card types
	if (ObtainableCards.Num() < number) {
		UE_LOG(LogTemp, Error, TEXT("Game mode/Generate random obtainable cards: too much cards to generate (%i/%i)"), number, ObtainableCards.Num());
		return TArray<TSubclassOf<ACard>>();
	}
	// If it is equal, all types are returned
	else if (ObtainableCards.Num() == number) {
		TArray<TSubclassOf<ACard>> temp;
		ObtainableCards.GenerateKeyArray(temp);
		return temp;
	}


	UE_LOG(LogTemp, Warning, TEXT("%i"), number)
	TArray<TSubclassOf<ACard>> temp;
	
	auto cardsWeight = GetObtainableCardsWeight();
	auto ObtainableCopy = ObtainableCards;
	
	
	for (auto i = 0; i < number; ++i) {
		uint16 rnd = FMath::RandRange(0, cardsWeight);
		
		// Ensures every card will appear only once
		for (const auto [key, value] : ObtainableCopy) {
			if (rnd <= value) {
				temp.Add(key);
				cardsWeight -= ObtainableCopy[key];
				ObtainableCopy.Remove(key);
				break;
			}
			else rnd -= value;
		}
	}

	return temp;
}

void AKarciankaGameModeBase::GenerateRandomObtainableCards(TArray<TSubclassOf<ACard>>& temp, uint8 number) {
	// Number must be lesser or equal than the number of card types
	if (ObtainableCards.Num() < number) {
		UE_LOG(LogTemp, Error, TEXT("Game mode/Generate random obtainable cards: too much cards to generate (%i/%i)"), number, ObtainableCards.Num());
		return;
	}
	// If it is equal, all types are returned
	else if (ObtainableCards.Num() == number) {
		ObtainableCards.GenerateKeyArray(temp);
	}

	auto cardsWeight = GetObtainableCardsWeight();
	auto ObtainableCopy = ObtainableCards;


	for (auto i = 0; i < number; ++i) {
		uint16 rnd = FMath::RandRange(0, cardsWeight);

		// Ensures every card will appear only once
		for (const auto [key, value] : ObtainableCopy) {
			if (rnd <= value) {
				temp.Add(key);
				cardsWeight -= ObtainableCopy[key];
				ObtainableCopy.Remove(key);
			}
			else rnd -= value;
		}
	}
}

uint16 AKarciankaGameModeBase::GetObtainableCardsWeight() {
	TArray<uint8> values;
	ObtainableCards.GenerateValueArray(values);
	uint16 temp = 0;
	for (const auto& e : values) {
		temp += e;
	}
	return temp;
}