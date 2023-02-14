// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

// Sets default values
AEnemyPawn::AEnemyPawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HandSize = 5;
	mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = mesh;
	canvas = CreateDefaultSubobject<UWidgetComponent>(TEXT("canvas"));
	canvas->SetupAttachment(mesh);
	canvas->SetWidgetSpace(EWidgetSpace::Screen);
}

// Called when the game starts or when spawned
void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyPawn::ReceiveDamage(const uint8& damage) {
	hp -= damage;
}

void AEnemyPawn::AutoAttack() {
	//TODO: after creating player class, change to Receive Damage call or similar
	auto playerState = GetWorld()->GetFirstPlayerController()->GetPlayerState<AMyPlayerState>();
	if (playerState == NULL) {
		UE_LOG(LogTemp, Error, TEXT("Player state is null"));
		return;
	}

	TArray<TSubclassOf<ACard>> keys;
	Hand.GetKeys(keys);
	ACard* BestCard = NULL;
	for (const auto& key : keys) {
		auto card = key.GetDefaultObject();
		if (card->IsOfType(EffectType::attack)) {
			if (BestCard == NULL) {
				BestCard = card;
			}
			else if (BestCard->GetSumaricEffects(EffectType::attack) < card->GetSumaricEffects(EffectType::attack)) {
				BestCard = card;
			}
		}
	}
	playerState->SetHP(playerState->GetHP() - BestCard->GetSumaricEffects(EffectType::attack));
	auto BestCardClass = BestCard->StaticClass();
	--Hand[BestCardClass];
	if (Hand[BestCardClass] == 0) {
		Hand.Remove(BestCardClass);
	}
}

void AEnemyPawn::AutoHeal() {
	TArray<TSubclassOf<ACard>> keys;
	Hand.GetKeys(keys);
	ACard* BestCard = NULL;
	for (const auto& key : keys) {
		auto card = key.GetDefaultObject();
		if (card->IsOfType(EffectType::heal)) {
			if (BestCard == NULL) {
				BestCard = card;
			}
			else if (abs(maxHP - hp - BestCard->GetSumaricEffects(EffectType::heal)) > abs(maxHP - hp - card->GetSumaricEffects(EffectType::heal))) {
				BestCard = card;
			}
		}
	}
	Play(BestCard, this);
	auto BestCardClass = BestCard->StaticClass();
	--Hand[BestCardClass];
	if (Hand[BestCardClass] == 0) {
		Hand.Remove(BestCardClass);
	}
}

void AEnemyPawn::UpdateHealthBar() {

}

const TMap<TSubclassOf<ACard>, uint8>& ACardPawn::GetDeck() {
	return this->Deck;
}

const TMap<TSubclassOf<ACard>, uint8>& ACardPawn::GetHand() {
	return this->Hand;
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
}

void ACardPawn::AutoHeal() {
	UE_LOG(LogTemp, Error, TEXT("Don't use ACardPawn by itself, it's supposed to be abstract class"));
}

void ACardPawn::AutoAttack() {
	UE_LOG(LogTemp, Error, TEXT("Don't use ACardPawn by itself, it's supposed to be abstract class"));
}

void ACardPawn::Heal(const uint8& damage) {
	UE_LOG(LogTemp, Error, TEXT("Don't use ACardPawn by itself, it's supposed to be abstract class"));
}

void ACardPawn::UpdateHealthBar() {
	UE_LOG(LogTemp, Error, TEXT("Don't use ACardPawn by itself, it's supposed to be abstract class"));
}

void ACardPawn::ReceiveDamage(const uint8& damage) {
	UE_LOG(LogTemp, Error, TEXT("Don't use ACardPawn by itself, it's supposed to be abstract class"));
}