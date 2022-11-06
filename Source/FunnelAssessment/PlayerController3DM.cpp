// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerController3DM.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/GameState.h"
#include "GameFramework/PlayerState.h"
#include "MultiplayerGamemode.h"
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
	Health = FindComponentByClass<UHealthComponent>();

	bUseControllerRotationPitch = true;

	// set the movement component and update the movement to the custom variables
	MoveComponent = GetCharacterMovement();
	SetMovementMode();

	// Set the opponent as target and spawn funnels
	SetTarget();

	// Turn this off when in use
	//SpawnFunnels();
}

// Called every frame
void APlayerController3DM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Attempt to set the target if its not already set
	if (!FunnelTarget)
	{
		SetTarget();
	}
	// Run the check for boost
	BoostCheck2();
}

void APlayerController3DM::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(APlayerController3DM, bBoostActive);
	DOREPLIFETIME(APlayerController3DM, Funnels);
	DOREPLIFETIME(APlayerController3DM, bPreventLockon);
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

	// Set boost speed based on FlySpeed and multiplier
	BoostSpeed = FlySpeed * BoostMultiplier;
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

// NOT USED
void APlayerController3DM::BoostCheck()
{
	// boost if players is not on a cooldown
	if (bBoostActive)
	{
		if (!bBoostCooldown)
		{
			if (BoostTime < MaxBoostDuration)
			{
				BoostTime += (GetWorld()->GetDeltaSeconds())/2;
				MoveComponent->MaxFlySpeed = BoostSpeed;
				//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("%f"), (BoostTime / MaxBoostDuration) * 100));
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
			//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("%f"), (BoostTime / MaxBoostDuration) * 100));
		}
		// allow player to boost again/reset cooldown if the boost is fully recovered
		if (BoostTime <= 0.0f)
		{
			BoostTime = 0.0f;
			bBoostCooldown = false;
		}
	}
}

void APlayerController3DM::BoostCheck2()
{
	// Allow player to boost until BoostTime reaches the Max duration
	if (bBoostActive)
	{
		if (BoostTime < MaxBoostDuration)
		{
			// Increase FOV for better emphasis
			Camera->SetFieldOfView(BoostFOV);
			BoostTime += GetWorld()->GetDeltaSeconds();
			MoveComponent->MaxFlySpeed = BoostSpeed;
			// force turn off boost when max duration is met
			if (BoostTime >= MaxBoostDuration)
			{
				GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("No boost fuel")));
				bBoostActive = false;
			}
		}
	}
	// Restore BoostTime when player is not using boost
	if (!bBoostActive)
	{
		// Reset FOV back to normal
		Camera->SetFieldOfView(NormalFOV);
		MoveComponent->MaxFlySpeed = FlySpeed;
		if (BoostTime > 0.0f)
		{
			BoostTime -= GetWorld()->GetDeltaSeconds();
		}

	}
	LockonCheck();
}

// turn bPreventLockon depending on if the player is boosting or not
void APlayerController3DM::LockonCheck()
{
	bPreventLockon = bBoostActive;
}

void APlayerController3DM::BoostOn()
{
	ServerBoostOn();
}

void APlayerController3DM::ServerBoostOn_Implementation()
{
	bBoostActive = true;
}

void APlayerController3DM::BoostOff()
{
	ServerBoostOff();
}

void APlayerController3DM::ServerBoostOff_Implementation()
{
	bBoostActive = false;
}

void APlayerController3DM::SetTarget()
{
	// Get all the player actors in the world and set the opponent as target
	for (TActorIterator<APlayerController3DM> It(GetWorld()); It; ++It)
	{
		// Get the gamestate to access the array keeping all the players
		AGameStateBase* GameState = GetWorld()->GetGameState();
		for (int i = 0; i < GameState->PlayerArray.Num(); i++)
		{
			APlayerController3DM* OtherPlayer = Cast<APlayerController3DM>(GameState->PlayerArray[i]->GetPawn());
			// Set the player as the funnel target when its not the same as this player (ie the opponent)
			if (OtherPlayer != this)
			{
				FunnelTarget = OtherPlayer;
			}
		}
	}
	// update the funnel target alongside it
	SetFunnelTarget();
}

void APlayerController3DM::SpawnFunnels()
{
	// spawn funnels on client or server
	if (IsLocallyControlled())
	{
		ServerSpawnFunnels();
	}
}


// Server Implementation of SpawnFunnels, should be called when the player is controlled pawn
void APlayerController3DM::ServerSpawnFunnels_Implementation()
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
			SetFunnelTarget();
		}
	}
}

// Set the funnel's FollowTarget to this FunnelTarget
void APlayerController3DM::SetFunnelTarget()
{
	if (FunnelTarget)
	{
		for (int i = 0; i < Funnels.Num(); i++)
		{
			if (Funnels[i])
			{
				Funnels[i]->FollowTarget = FunnelTarget;
			}
		}
	}
}

// Call the gamemode function to delete this character
void APlayerController3DM::OnDeath()
{
	AMultiplayerGamemode* Gamemode = Cast<AMultiplayerGamemode>(GetWorld()->GetAuthGameMode());
	if (Gamemode)
	{
		Gamemode->PlayerDeath(GetController());
	}
}


// Reset health back to maxHealth when the player respawns, called by multiplayergamemode
void APlayerController3DM::Respawn()
{
	if (Health)
	{
		Health->CurrentHealth = Health->MaxHealth;
	}
}