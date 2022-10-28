// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController3DM.h"
#include "Net/UnrealNetwork.h"
#include "Components/InputComponent.h"

// Sets default values
APlayerController3DM::APlayerController3DM()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bReplicates = true;
}

// Called when the game starts or when spawned
void APlayerController3DM::BeginPlay()
{
	Super::BeginPlay();
	

	Camera = FindComponentByClass<UCameraComponent>();
	bUseControllerRotationPitch = true;

	// set the movement component and update the movement to the custom variables
	MoveComponent = GetCharacterMovement();
	SetMovementMode();

	// Spawns the funnels
	SpawnFunnels();

	BoostSpeed = FlySpeed * BoostMultiplier;
}

// Called every frame
void APlayerController3DM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	BoostCheck();
}

void APlayerController3DM::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerController3DM, bBoostActive);
	DOREPLIFETIME(APlayerController3DM, bBoostCooldown);
	DOREPLIFETIME(APlayerController3DM, BoostTime);
	DOREPLIFETIME(APlayerController3DM, BoostCooldown);
}

// setting player movement
void APlayerController3DM::SetMovementMode()
{	
	ServerSetMovementMode();
	// set move mode as flying
	MoveComponent->SetMovementMode(EMovementMode::MOVE_Flying);
	// set move speed from custom vars
	MoveComponent->MaxFlySpeed = FlySpeed;
	MoveComponent->BrakingDecelerationFlying = FlyDeceleration;
}

// sever replication of setting player movement
void APlayerController3DM::ServerSetMovementMode_Implementation()
{
	// set move mode as flying
	MoveComponent->SetMovementMode(EMovementMode::MOVE_Flying);
	// set move speed from custom vars
	MoveComponent->MaxFlySpeed = FlySpeed;
	MoveComponent->BrakingDecelerationFlying = FlyDeceleration;
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

	PlayerInputComponent->BindAction(TEXT("Boost"), EInputEvent::IE_Pressed, this, &APlayerController3DM::BoostOn);
	PlayerInputComponent->BindAction(TEXT("Boost"), EInputEvent::IE_Released, this, &APlayerController3DM::BoostOff);
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
	FRotator LookUpRotation = FRotator::ZeroRotator;
	LookUpRotation.Pitch = val;
	if (Camera)
	{
		if (abs(Camera->GetRelativeRotation().Pitch + LookUpRotation.Pitch >= 90.0f)) {

			return;
		}
		Camera->AddRelativeRotation(LookUpRotation);
		FRotator RelativeRotation = Camera->GetRelativeRotation();
		RelativeRotation.Yaw = 0.0f;
		RelativeRotation.Roll = 0.0f;
		Camera->SetRelativeRotation(RelativeRotation);
	}
}

void APlayerController3DM::BoostCheck()
{

	// boost if players is not on a cooldown
	if (bBoostActive)
	{
		if (!bBoostCooldown)
		{
			if (BoostTime < MaxBoostDuration)
			{
				BoostTime += GetWorld()->GetDeltaSeconds();
				MoveComponent->MaxFlySpeed = BoostSpeed;
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("%f"), (BoostTime / MaxBoostDuration) * 100));
			}
			// force cooldown when boost is used up
			if (BoostTime >= MaxBoostDuration)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("No boost fuel")));
				bBoostActive = false;
				bBoostCooldown = true;
			}
		}
	}

	// restore boost when inactive
	if (!bBoostActive)
	{	
		MoveComponent->MaxFlySpeed = FlySpeed;
		// restore boost when player is not using boost
		if (BoostTime > 0.0f)
		{
			BoostTime -= GetWorld()->GetDeltaSeconds();
			GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("%f"), (BoostTime / MaxBoostDuration) * 100));
		}
		// allow player to boost again/reset cooldown if the boost is fully recovered
		if (BoostTime <= 0.0f)
		{
			BoostTime = 0.0f;
			bBoostCooldown = false;
		}
	}

}

void APlayerController3DM::BoostOn()
{
	bBoostActive = true;
}

void APlayerController3DM::BoostOff()
{
	bBoostActive = false;
}

void APlayerController3DM::SpawnFunnels()
{
	// Fills the Funnels TArray by spawning the set amount of funnels spaced out in equal length
	if (FunnelClass)
	{
		for (int i = 0; i < FunnelAmt; i++)
		{
			FVector root = this->GetActorLocation();
			// Set the initial spawn location
			FVector SpawnOffset = root;
			SpawnOffset.Z += FunnelOffset;
			SpawnOffset.Y += ((FunnelOffset * FunnelAmt) / -2) + (FunnelOffset * i);
			ABoids* NewFunnel = GetWorld()->SpawnActor<ABoids>(FunnelClass, SpawnOffset, this->GetActorRotation());
			Funnels.Add(NewFunnel);
			NewFunnel->SpawnDefaultController();
			// sets the funnel's target
			if (FunnelTarget)
			{
				NewFunnel->FollowTarget = FunnelTarget;
			}
		}
	}
}