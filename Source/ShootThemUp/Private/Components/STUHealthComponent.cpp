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
    if (const auto ComponentOwner = GetOwner())
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
    }
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser)
{
    Health -= Damage;
}