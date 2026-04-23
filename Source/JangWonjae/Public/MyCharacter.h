#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

USTRUCT(BlueprintType)
struct FMyItemInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Description;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 AttackPower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 DefensePower;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Rarity;
};

USTRUCT(BlueprintType)
struct FItemData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemID;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemLevel;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString RequiredTitle;
};

UCLASS()
class JANGWONJAE_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FItemData> Inventory;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TMap<FString, FMyItemInfo> ItemDatabase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSet<FString> AcquiredTitles;

	FString ActiveTitle;

	void AddItem(const FItemData& Item);
	void AcquireTitle(const FString& Title);
	bool UseItem(const FString& ItemID);
	FMyItemInfo* GetItemInfo(const FString& ItemID);

};
