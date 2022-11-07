// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGamemode.h"
#include "PlayerController3DM.h"
#include "TimerManager.h"

// Call from playercharacter when theyre dead
void AMultiplayerGamemode::PlayerDeath(AController* Controller)
{
	if (Controller)
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("%s is dead"), *Controller->GetName()));
		UE_LOG(LogTemp, Warning, TEXT("%s is dead"), *Controller->GetName());
		Controller->GetPawn()->SetLifeSpan(0.1);

		// Set timer to respawn
		FTimerHandle RespawnTimer;
		FTimerDelegate RespawnDelegate;
		RespawnDelegate.BindUFunction(this, TEXT("PlayerRespawn"), Controller);
		GetWorldTimerManager().SetTimer(RespawnTimer, RespawnDelegate, 5.0f, false);
	}
}


// Spawn the player again and call the Respawn() function
void AMultiplayerGamemode::PlayerRespawn(AController* Controller)
{
	if (Controller)
	{
		AActor* SpawnPoint = ChoosePlayerStart(Controller);
		if (SpawnPoint)
		{
			APawn* SpawnedPlayer = GetWorld()->SpawnActor<APawn>(DefaultPawnClass, SpawnPoint->GetActorLocation(), SpawnPoint->GetActorRotation());
			if (SpawnedPlayer)
			{
				Controller->Possess(SpawnedPlayer);
				Cast<APlayerController3DM>(Controller->GetPawn())->Respawn();
			}
		}
	}
}