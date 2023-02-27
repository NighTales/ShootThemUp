// Shoot Them Up Game, All Rights Reserved.

#include "Components/STUHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(HeathLog, All, All)

USTUHealthComponent::USTUHealthComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

float USTUHealthComponent::GetHealth() const
{
    return Health;
}

bool USTUHealthComponent::IsDead() const
{
    return FMath::IsNearlyZero(Health) ;
}

void USTUHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    SetHealth(MaxHealth);

    if (auto const ComponentOwner = GetOwner())
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);

        if (IsAutoHealEnabled)
        {
            GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::OnHealTimerUpdated, HealUpdateRate,
                true, HealDelay);
        }
    }
}

void USTUHealthComponent::SetHealth(const float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
    AActor* DamageCauser)
{
    if (Damage <= 0.0f || IsDead() || !GetWorld())
    {
        return;
    }

    SetHealth(Health - Damage);

    GetWorld()->GetTimerManager().PauseTimer(HealTimerHandle);

    if (IsDead())
    {
        OnDeath.Broadcast();
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
    else if (IsAutoHealEnabled)
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTUHealthComponent::OnHealTimerUpdated,
            HealUpdateRate, true, HealDelay);
    }
}

void USTUHealthComponent::OnHealTimerUpdated()
{
    SetHealth(Health + HealthPerTime);

    if (FMath::IsNearlyEqual(Health, MaxHealth) && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}