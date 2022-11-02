// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiplayerGamemode.h"

void AMultiplayerGamemode::PlayerDeath(AController* Controller)
{
	if (Controller)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s is dead"), *Controller->GetName());
		Controller->GetPawn()->SetLifeSpan(0.1);
	}
}