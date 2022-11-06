// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"
#include "PlayerController3DM.h"
#include "PlayerHUD.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	// Set the currenthealt ot the max health on start
	CurrentHealth = MaxHealth;
	UpdateHealthbar();
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UHealthComponent, CurrentHealth);
}

void UHealthComponent::TakeDamage()
{
	CurrentHealth--;
	UpdateHealthbar();

	APlayerController3DM* Owner = Cast<APlayerController3DM>(GetOwner());
	if (Owner)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s Health: %f"), *Owner->GetName(), CurrentHealth);
		//GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, FString::Printf(TEXT("%s Health: %f"), *Owner->GetName(), CurrentHealth));
	}

	if (Owner && CurrentHealth <= 0.0f)
	{
		Owner->OnDeath();
	}	
}

void UHealthComponent::UpdateHealthbar()
{
	if (Cast<APawn>(GetOwner())->IsLocallyControlled())
	{
		APlayerHUD* PlayerHUD = Cast<APlayerHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetHUD());
		if (PlayerHUD)
		{
			PlayerHUD->SetHealthbarAmt(CurrentHealth / MaxHealth);
		}
	}
}