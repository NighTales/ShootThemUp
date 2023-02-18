// Shoot Them Up Game, All Rights Reserved.


#include "Components/STUCharacterMovementComponent.h"

#include "STUCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ASTUCharacter* Player = Cast<ASTUCharacter>(GetPawnOwner());
    const float Speed = Player && Player->IsSprintAvailable() ? MaxSpeed * SprintModifier : MaxSpeed;

    return Speed;
}