// Fill out your copyright notice in the Description page of Project Settings.


#include "ACardPawn.h"

// number - of cards to draw
void ACardPawn::DrawCards(uint8 number) {
	if (HandWeight + number > HandSize)
		number = HandSize - HandWeight;

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
			TArray<uint8> weights;
			Stack.GenerateValueArray(weights);
			StackWeight = 0;
			for (const auto& e : weights) StackWeight += e;
		}
	}

	HandWeight += number;
}

void ACardPawn::DiscardCardsOfClass(TSubclassOf<ACard> cardType, uint8 number){
	HandWeight -= (number <= Hand[cardType]) ? number : Hand[cardType];
	Hand[cardType] -= number;
	if (Hand[cardType] <= 0)
		Hand.Remove(cardType);
}

void ACardPawn::DiscardCards(ACard* card, uint8 number) {
	auto cardType = card->GetClass();
	HandWeight -= (number <= Hand[cardType]) ? number : Hand[cardType];
	Hand[cardType] -= number;
	if (Hand[cardType] <= 0)
		Hand.Remove(cardType);
}

void ACardPawn::StartFight() {
	if (bInFight)
		return;
	bInFight = true;
	bTurnEnded = false;

	APcurrent = APstarting;

	// Empties stack of cards, then fills it with deck values
	Stack.Empty();
	Stack = Deck;

	// Calculates cumulative weight of stack for drawing
	TArray<uint8> weights;
	Stack.GenerateValueArray(weights);
	StackWeight = 0;
	for (const auto& e : weights) StackWeight += e;

	Hand.Empty();
	HandWeight = 0;
	DrawCards(HandSize);
	///UE_LOG(LogTemp, Warning, TEXT("%s"), HasCardOfType(EffectType::attack) ? *FString("Has attack card") : *FString("Doesn't have attack card"))
}

void ACardPawn::StartTurn() {
	bTurnEnded = false;
	DrawCards(DrawnCards);
	APcurrent += APgain;
}

void ACardPawn::EndTurn() {
	bTurnEnded = true;
}

bool ACardPawn::HasCardOfType(EffectType type) {
	//Iterates over all cards and gets the defaults
	//if the default card contains an effect of type, returns true
	//else returns false after iterating over all card types in hand
	for (const auto& [CardType, number] : this->Hand) {
		ACard* Card = GetDefaultCard(CardType);
		bool isOfType = Card->IsOfType(type);
		//UE_LOG(LogTemp, Warning, TEXT("%s: %s"), *Card->GetFName().ToString(), isOfType ? *FString("It's an attack card") : *FString("It's not an attack card"));
		if (isOfType)
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

void ACardPawn::Play(ACard* card, ACardPawn* cardTarget) {
	if (!EnoughAPToPlay(card)) {
		IndicateNoAP(card);
		return;
	}


	for (const auto& effect : card->GetEffects()) {
		ACardPawn* target;
		if (effect.target == EffectTarget::self)
			target = this;
		else
			target = cardTarget;

		switch (effect.type) {
		case EffectType::attack:
			target->ReceiveDamage(effect.value);
			break;
		case EffectType::heal:
			target->Heal(effect.value);
			break;
		case EffectType::gainAP:
			target->GainAP(effect.value);
			break;
		}
	}
	cardTarget->UpdateHealthBar();
	UpdateHealthBar();

	UClass* cardClass = card->GetClass();
	Hand[cardClass] -= 1;
	if (Hand[cardClass] <= 0)
		Hand.Remove(cardClass);

	HandWeight--;
	APcurrent -= card->APcost;
}

void ACardPawn::UpdateHealthBar() {
	if (ProgressBar == NULL || HPText == NULL)
		return;

	ProgressBar->SetPercent((float)hp / (float)maxHP);
	HPText->SetText(FText::FromString(FString::FromInt(hp)+"/"+FString::FromInt(maxHP)));
}

UProgressBar* ACardPawn::GetProgressBar() {
	return ProgressBar;
}

void ACardPawn::SetProgressBar(UProgressBar* progressBar) {
	ProgressBar = progressBar;
}

bool ACardPawn::EnoughAPToPlay(ACard* card) {
	return card->APcost <= APcurrent;
}

void ACardPawn::IndicateNoAP_Implementation(ACard* ExpansiveCard) {
	UE_LOG(LogTemp, Warning, TEXT("%s: I have not enough Action Points (%i) for using %s (%i)"), *GetFName().ToString(), APcurrent, *ExpansiveCard->GetFName().ToString(), ExpansiveCard->APcost);
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

void ACardPawn::GainAP(const uint8& value) {
	UE_LOG(LogTemp, Error, TEXT("Gain AP: Don't use ACardPawn by itself, it's supposed to be abstract class"));
}