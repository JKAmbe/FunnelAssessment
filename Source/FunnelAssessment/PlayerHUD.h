// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

/**
 * 
 */
UCLASS()
class FUNNELASSESSMENT_API APlayerHUD : public AHUD
{
	GENERATED_BODY()
	
private:
	TSubclassOf<class UUserWidget> PlayerHUDClass;
	UUserWidget* PlayerHUDWidget;
	class UProgressBar* HealthBar;
	class UProgressBar* BoostBar;

public:
	APlayerHUD();
	void SetHealthbarAmt(float Percent);
	void SetBoostbarAmt(float Percent);
};
