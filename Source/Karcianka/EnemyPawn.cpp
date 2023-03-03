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
	auto playerPawn = GetWorld()->GetFirstPlayerController()->GetOwner<ACardPawn>();
	if (playerPawn == NULL) {
		UE_LOG(LogTemp, Error, TEXT("Player is null"));
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
	playerPawn->ReceiveDamage(BestCard->GetSumaricEffects(EffectType::attack));
	auto BestCardClass = BestCard->StaticClass();
	Hand[BestCardClass]-=1;
	if (Hand[BestCardClass] == 0) {
		Hand.Remove(BestCardClass);
	}
	playerPawn->UpdateHealthBar();
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