// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MultiplayerGamemode.generated.h"

/**
 * 
 */
UCLASS()
class FUNNELASSESSMENT_API AMultiplayerGamemode : public AGameMode
{
	GENERATED_BODY()
	
public:
	void PlayerDeath(AController* Controller);
	UFUNCTION()
		void PlayerRespawn(AController* Controller);
};
