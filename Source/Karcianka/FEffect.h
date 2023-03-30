#pragma once

#include "CoreMinimal.h"
#include "Misc/Crc.h"
#include "FEffect.generated.h"

UENUM(BlueprintType)
enum class EffectType : uint8 {
	heal,
	attack,
	gainAP,
};

UENUM(BlueprintType)
enum class EffectTarget : uint8 {
	self, ally, enemy, any
};

USTRUCT(BlueprintType)
struct FEffect {
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite)
		EffectType type;

	UPROPERTY(BlueprintReadWrite)
		EffectTarget target;

	UPROPERTY(BLueprintReadWrite)
		int value;

	FEffect() : type(EffectType::heal), target(EffectTarget::self), value(0) {}

	FEffect(EffectType _type, EffectTarget _target, int _value) : type(_type), target(_target), value(_value) {}

	FEffect(const FEffect& other) : type(other.type), target(other.target), value(other.value) {}

	bool operator== (const FEffect& other) const {
		return Equals(other);
	}

	bool operator!= (const FEffect& other) const {
		return !Equals(other);
	}

	bool Equals(const FEffect& other) const {
		return type == other.type && target == other.target && value == other.value;
	}
};

FORCEINLINE uint32 GetTypeHash(const FEffect& Thing)
{
	uint32 Hash = FCrc::MemCrc32(&Thing, sizeof(FEffect));
	return Hash;
}