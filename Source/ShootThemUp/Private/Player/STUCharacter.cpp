// Shoot Them Up Game, All Rights Reserved.


#include "Player/STUCharacter.h"

#include "Components/STUCharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ASTUCharacter::ASTUCharacter(const FObjectInitializer& ObjInit)
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
void ASTUCharacter::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void ASTUCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ASTUCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &ASTUCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &ASTUCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &ASTUCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &ASTUCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ASTUCharacter::Jump);
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &ASTUCharacter::SprintStart);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this, &ASTUCharacter::SprintEnd);
}

bool ASTUCharacter::IsSprintAvailable() const
{
    const bool Result = WantToSprint && IsMovingForward && !GetVelocity().IsZero();
    return Result;
}

float ASTUCharacter::GetMovementDirection() const
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

void ASTUCharacter::MoveForward(float Value)
{
    IsMovingForward = Value > 0;
    AddMovementInput(GetActorForwardVector(), Value);
}

void ASTUCharacter::MoveRight(float Value)
{
    AddMovementInput(GetActorRightVector(), Value);
}

void ASTUCharacter::SprintStart()
{
    WantToSprint = true;
}

void ASTUCharacter::SprintEnd()
{
    WantToSprint = false;
}