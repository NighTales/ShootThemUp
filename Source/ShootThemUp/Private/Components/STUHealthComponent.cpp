// Shoot Them Up Game, All Rights Reserved.

#include "Components/STUHealthComponent.h"

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
    Health = MaxHealth;
}

float USTUHealthComponent::GetHealth() const
{
    return Health;
}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();
}