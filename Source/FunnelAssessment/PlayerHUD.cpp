// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Blueprint/UserWidget.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/ProgressBar.h"

APlayerHUD::APlayerHUD()
{
	static ConstructorHelpers::FClassFinder<UUserWidget> PlayerHUDObject(TEXT("/Game/Widget/PlayerHUDWidget"));
	PlayerHUDClass = PlayerHUDObject.Class;

	if (PlayerHUDClass)
	{
		PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDClass);
		if (PlayerHUDWidget)
		{
			PlayerHUDWidget->AddToViewport();
		}
	}
	if (PlayerHUDWidget)
	{
		HealthBar = Cast<UProgressBar>(PlayerHUDWidget->GetWidgetFromName(TEXT("HealthBar")));
		BoostBar = Cast<UProgressBar>(PlayerHUDWidget->GetWidgetFromName(TEXT("BoostBar")));
	}
}

void APlayerHUD::SetHealthbarAmt(float Percent)
{
	if (HealthBar)
	{
		HealthBar->SetPercent(Percent);
	}
}

void APlayerHUD::SetBoostbarAmt(float Percent)
{
	if (BoostBar)
	{
		BoostBar->SetPercent(Percent);
	}
}
