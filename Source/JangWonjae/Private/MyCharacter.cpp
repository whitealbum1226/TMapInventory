#include "MyCharacter.h"

void AMyCharacter::AddItem(const FItemData& Item)
{
    if (Inventory.Num() < 20)
    {
        Inventory.Add(Item);
        UE_LOG(LogTemp, Log, TEXT("아이템 추가: %s"), *Item.ItemName);
    }
}

FMyItemInfo* AMyCharacter::GetItemInfo(const FString& ItemID)
{
    if (FMyItemInfo* Info = ItemDatabase.Find(ItemID))
    {
        UE_LOG(LogTemp, Log, TEXT("아이템 조회 성공: %s"), *ItemID);
        return Info;
    }
    return nullptr;
}

void AMyCharacter::AcquireTitle(const FString& Title)
{
    if (AcquiredTitles.Contains(Title))
    {
        UE_LOG(LogTemp, Log, TEXT("이미 보유한 칭호: %s"), *Title);
        return;
    }

    AcquiredTitles.Add(Title);
    UE_LOG(LogTemp, Log, TEXT("새 칭호 획득: %s"), *Title);
}

bool AMyCharacter::UseItem(const FString& ItemID)
{
    FItemData* Found = Inventory.FindByPredicate(
        [&ItemID](const FItemData& Item) {
            return Item.ItemID == ItemID;
        });

    if (!Found) return false;

    if (!Found->RequiredTitle.IsEmpty() &&
        !AcquiredTitles.Contains(Found->RequiredTitle))
    {
        UE_LOG(LogTemp, Warning, TEXT("칭호 부족: %s 필요"), *Found->RequiredTitle);
        return false;
    }

    if (FMyItemInfo* Info = ItemDatabase.Find(ItemID))
    {
        UE_LOG(LogTemp, Log, TEXT("아이템 사용: 공격력 +%d"),
            Info->AttackPower);
        Inventory.RemoveAll([&ItemID](const FItemData& i) {
            return i.ItemID == ItemID;
            });
        return true;
    }
    return false;
}

void AMyCharacter::BeginPlay()
{
    Super::BeginPlay();

    FMyItemInfo SwordInfo;
    SwordInfo.Description = "전설급 검";
    SwordInfo.AttackPower = 999;
    SwordInfo.DefensePower = 999;
    SwordInfo.Rarity = "Legendary";
    ItemDatabase.Add("IT01", SwordInfo);

    FMyItemInfo BowInfo;
    BowInfo.Description = "전설급 활";
    BowInfo.AttackPower = 999;
    BowInfo.DefensePower = 999;
    BowInfo.Rarity = "Legendary";
    ItemDatabase.Add("IT02", BowInfo);

    FMyItemInfo PotionInfo;
    PotionInfo.Description = "회복 포션";
    PotionInfo.AttackPower = 0;
    PotionInfo.DefensePower = 0;
    PotionInfo.Rarity = "Common";
    ItemDatabase.Add("IT03", PotionInfo);

    FItemData Sword;
    Sword.ItemID = "IT01";
    Sword.ItemName = "엑스칼리버";
    Sword.ItemLevel = 99;
    Sword.RequiredTitle = "왕";
    AddItem(Sword);

    FItemData Bow;
    Bow.ItemID = "IT02";
    Bow.ItemName = "페일노트";
    Bow.ItemLevel = 99;
    Bow.RequiredTitle = "영웅";
    AddItem(Bow);

    FItemData Potion;
    Potion.ItemID = "IT03";
    Potion.ItemName = "소형 체력 회복 포션";
    Potion.ItemLevel = 1;
    Potion.RequiredTitle = "";
    AddItem(Potion);

    AcquireTitle("영웅");
}
