// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController3DM.h"
#include "Components/InputComponent.h"

// Sets default values
APlayerController3DM::APlayerController3DM()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerController3DM::BeginPlay()
{
	Super::BeginPlay();
	
	Camera = FindComponentByClass<UCameraComponent>();
	MoveComponent = GetCharacterMovement();
}

// Called every frame
void APlayerController3DM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerController3DM::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerController3DM::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Strafe"), this, &APlayerController3DM::Strafe);
	PlayerInputComponent->BindAxis(TEXT("MoveVertical"), this, &APlayerController3DM::MoveVertical);
	PlayerInputComponent->BindAxis(TEXT("LookX"), this, &APlayerController3DM::LookX);
	PlayerInputComponent->BindAxis(TEXT("LookY"), this, &APlayerController3DM::LookY);


}

void APlayerController3DM::MoveForward(float val)
{
	FRotator Forward = GetControlRotation();
	Forward.Roll = 0.0f;
	Forward.Pitch = 0.0f;
	AddMovementInput(Forward.Vector(), val);
}

void APlayerController3DM::Strafe(float val)
{
	AddMovementInput(GetActorRightVector(), val);
}

void APlayerController3DM::MoveVertical(float val)
{
	AddMovementInput(GetActorUpVector(), val);
}

void APlayerController3DM::LookX(float val)
{
	AddControllerYawInput(val);
}

void APlayerController3DM::LookY(float val)
{
	AddControllerPitchInput(val);
}

