// Shoot Them Up Game, All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STUBaseCharacter.generated.h"

class USTUWeaponComponent;
class UTextRenderComponent;
class USTUHealthComponent;
class USpringArmComponent;
class UCameraComponent;
UCLASS()
class SHOOTTHEMUP_API ASTUBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    ASTUBaseCharacter(const FObjectInitializer& ObjInit);

protected:
    virtual void BeginPlay() override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UCameraComponent* CameraComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UCharacterMovementComponent* MovementComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    USTUHealthComponent* HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UTextRenderComponent* HealthTextComponent;

    UPROPERTY(EditDefaultsOnly, Category="Components")
    USTUWeaponComponent* WeaponComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Animation")
    UAnimMontage* DeathAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category="Damage")
    float LifeSpanOnDeath = 5.0f;

    UPROPERTY(EditDefaultsOnly, Category="Damage")
    FVector2D LandedDamageVelocity = FVector2D(900.f, 1200.f);

    UPROPERTY(EditDefaultsOnly, Category="Damage")
    FVector2D LandedDamage = FVector2D(10.f, 100.f);

public:
    virtual void Tick(float DeltaTime) override;

    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    UFUNCTION(BlueprintCallable, Category="Movement")
    bool IsSprintAvailable() const;

    UFUNCTION(BlueprintCallable, Category="Movement")
    float GetMovementDirection() const;

private:
    bool WantToSprint;
    bool IsMovingForward = false;
    void MoveForward(float Value);
    void MoveRight(float Value);
    void SprintStart();
    void SprintEnd();

    void OnDeath();
    void OnHealthChanged(float Health) const;

    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);
};