// Fill out your copyright notice in the Description page of Project Settings.


#include "ACardPawn.h"

const TMap<TSubclassOf<ACard>, uint8>& ACardPawn::GetDeck() {
	return this->Deck;
}

const TMap<TSubclassOf<ACard>, uint8>& ACardPawn::GetHand() {
	return this->Hand;
}

// number - of cards to draw
void ACardPawn::DrawCards(const uint8& number) {

	// Repeated for number of times
	for (uint8 i = 0; i < number; i++) {
		// Generates uniformly distributed number in <0, number of cards in stack>
		auto rnd = (uint8)FMath::RandRange(0, StackWeight);

		// Gets card dictated by random number and adds it to Hand
		for (const auto& [key, value] : Stack) {
			if (rnd <= value) {
				if (Hand.Contains(key))
					Hand[key] += 1;
				else {
					Hand.Add(key);
					Hand[key] = 1;
				}
				Stack[key] -= 1;
				break;
			}
			else rnd -= value;
		}

		//If there are no more cards in stack, discarded cards are put back
		if (--StackWeight == 0) {
			Stack.Empty();
			Stack = Deck;
			for (const auto& [key, value] : Hand) Stack[key] -= value;
		}
	}
}

void ACardPawn::StartFight() {
	// Empties stack of cards, then fills it with deck values
	Stack.Empty();
	Stack = Deck;

	// Calculates cumulative weight of stack for drawing
	TArray<uint8> weights;
	Stack.GenerateValueArray(weights);
	StackWeight = 0;
	for (const auto& e : weights) StackWeight += e;

	DrawCards(HandSize);
}

bool ACardPawn::HasCardOfType(EffectType type) {
	//Iterates over all cards and gets the defaults
	//if the default card contains an effect of type, returns true
	//else returns false after iterating over all card types in hand
	for (const auto& [CardType, number] : this->Hand) {
		auto Card = CardType.GetDefaultObject();
		for (const auto& effect : Card->GetEffects())
			if (effect.type == type)
				return true;
	}
	return false;
}

int ACardPawn::GetHP() {
	return hp;
}
int ACardPawn::GetMaxHP() {
	return maxHP;
}

void ACardPawn::Play(ACard* card, ACardPawn* target) {
	for (const auto& effect : card->GetEffects()) {
		switch (effect.type) {
		case EffectType::attack:
			target->ReceiveDamage(effect.value);
			break;
		case EffectType::heal:
			target->Heal(effect.value);
			break;
		}
	}

	UClass* cardClass = card->GetClass();
	Hand[cardClass] -= 1;
	if (Hand[cardClass] <= 0)
		Hand.Remove(cardClass);
}

void ACardPawn::UpdateHealthBar() {
	if (ProgressBar == NULL)
		return;

	ProgressBar->SetPercent(hp / maxHP);
}

UProgressBar* ACardPawn::GetProgressBar() {
	return ProgressBar;
}

void ACardPawn::SetProgressBar(UProgressBar* progressBar) {
	ProgressBar = progressBar;
}

void ACardPawn::AutoHeal() {
	UE_LOG(LogTemp, Error, TEXT("AutoHeal: Don't use ACardPawn by itself, it's supposed to be abstract class"));
}

void ACardPawn::AutoAttack() {
	UE_LOG(LogTemp, Error, TEXT("AutoAttack: Don't use ACardPawn by itself, it's supposed to be abstract class"));
}

void ACardPawn::Heal(const uint8& damage) {
	UE_LOG(LogTemp, Error, TEXT("Heal: Don't use ACardPawn by itself, it's supposed to be abstract class"));
}

void ACardPawn::ReceiveDamage(const uint8& damage) {
	UE_LOG(LogTemp, Error, TEXT("Receive Damage: Don't use ACardPawn by itself, it's supposed to be abstract class"));
}