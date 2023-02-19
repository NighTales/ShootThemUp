// Shoot Them Up Game, All Rights Reserved.


#include "Player/STUBaseCharacter.h"

#include "Components/STUCharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASTUBaseCharacter::ASTUBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ASTUBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ASTUBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASTUBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ASTUBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ASTUBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASTUBaseCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASTUBaseCharacter::SprintStart);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASTUBaseCharacter::SprintEnd);
}

bool ASTUBaseCharacter::IsSprintAvailable() const
{
    const bool Result = WantToSprint && IsMovingForward && !GetVelocity().IsZero();
    return Result;
}

float ASTUBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero())
    {
        return 0;
    }

    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto Angle = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(VelocityNormal, GetActorForwardVector());
    const auto Degrees = FMath::RadiansToDegrees(Angle);
    const float Direction = CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
    return Direction;
}

void ASTUBaseCharacter::MoveForward(float Value)
{
    IsMovingForward = Value > 0;
    AddMovementInput(GetActorForwardVector(), Value);
}

void ASTUBaseCharacter::MoveRight(float Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}

void ASTUBaseCharacter::SprintStart()
{
    WantToSprint = true;
}

void ASTUBaseCharacter::SprintEnd()
{
    WantToSprint = false;
}