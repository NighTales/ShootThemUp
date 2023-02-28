// Shoot Them Up Game, All Rights Reserved.


#include "Components/STUCharacterMovementComponent.h"

#include "STUBaseCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const ASTUBaseCharacter* Player = Cast<ASTUBaseCharacter>(GetPawnOwner());
    const float Speed = Player && Player->IsSprintAvailable() ? MaxSpeed * SprintModifier : MaxSpeed;

    return Speed;
}