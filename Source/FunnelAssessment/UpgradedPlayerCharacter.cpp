// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradedPlayerCharacter.h"
#include "GameFramework/GameState.h"
#include "GameFramework/PlayerState.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "AIController.h"
#include "Engine/Engine.h"
#include "Marker.h"

void AUpgradedPlayerCharacter::BeginPlay()
{
	
	Super::BeginPlay();
	for (TActorIterator<ABoids> It(GetWorld()); It; ++It) {
		Boids.Add(*It);
		LockedOnDG.BindUFunction(this, "LockedOn");
		((ABoids*)(*It))->LockedOn.Add(LockedOnDG);
	}

	MarkerComponent = FindComponentByClass<UWidgetComponent>();
	UMarker* MarkerWidget = (UMarker*)MarkerComponent->GetWidget();

	bReplicates = true;
	if (GetController())
		Controler = GetController();
}

void AUpgradedPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	UpdateOtherPlayerContent();
}

void AUpgradedPlayerCharacter::Tick(float Del)
{
	Super::Tick(Del);
	if (Controler)
	{
		
		BoidsVisibilityCheck();
		EnemyVisibilityCheck();		
	}
}

void AUpgradedPlayerCharacter::ChangeOwnership_Implementation(ABoids* Boid)
{
	for (AUpgradedPlayerCharacter* Enemy : OtherPlayers)
	{
		Enemy->ControlledBoids.Remove(Boid);
		UpdateUIOverride(this, Boid);
	}
}

void AUpgradedPlayerCharacter::SetFollowTarget_Implementation(bool bCanSee, AUpgradedPlayerCharacter* Caller)
{
	AUpgradedPlayerCharacter* RandEnemy =  Caller->OtherPlayers[FMath::RandRange(0, OtherPlayers.Num()-1)];
	if (bCanSee)
		for (ABoids* Boid : Caller->ControlledBoids)
			Boid->FollowTarget = RandEnemy;
	else
		for (ABoids* Boid : Caller->ControlledBoids)
			Boid->FollowTarget = nullptr;
}

void AUpgradedPlayerCharacter::UpdateUIOverride_Implementation(AUpgradedPlayerCharacter* Caller, ABoids* Boid)
{
	//OK, so in the BP version where I was testing, I did addunique in changeownership
	//but for WHATEVER reason in C++ , I have to do it here
	//ControlledBoids Is replicated, and the deletion is working Just fine inchange ownership! 
	//So why?! Am I a clown?!?!? WHAT IS THIS!?!?!
	ControlledBoids.AddUnique(Boid);					
	if (Caller->GetLocalRole() == ROLE_SimulatedProxy)
		for (ABoids* boid : ControlledBoids)
			((UMarker*)boid->MarkerComponent->GetWidget())->Reset();
}

void AUpgradedPlayerCharacter::LockedOn(ABoids* Boid)
{
	if (GetLocalRole() == ROLE_AutonomousProxy)
		ChangeOwnership(Boid);
}

void AUpgradedPlayerCharacter::UpdateOtherPlayerContent()
{
	AGameStateBase* GameSt = GetWorld()->GetGameState();
	for (APlayerState* PlayerSt : GameSt->PlayerArray)
	{
		AUpgradedPlayerCharacter* PlayerPawn = (AUpgradedPlayerCharacter*)PlayerSt->GetPawn();
		
		OtherPlayers.Add(PlayerPawn);
		PlayerPawn->OtherPlayers.Add(this);
	}
	
	OtherPlayers.Remove(this);
}

void AUpgradedPlayerCharacter::BoidsVisibilityCheck()
{
	for (ABoids* boid : Boids)
		boid->MarkerComponent->SetVisibility(ControlledBoids.Contains(boid) || IsOnScreen(boid));
}

void AUpgradedPlayerCharacter::EnemyVisibilityCheck()
{
	if (GetLocalRole() == ROLE_AutonomousProxy)
		for (AUpgradedPlayerCharacter* Enemy : OtherPlayers)
			if (Enemy)
			{
				bool visibility = IsOnScreen(Enemy);
				Enemy->MarkerComponent->SetVisibility(visibility);
				SetFollowTarget(visibility, this);
			}
}
bool AUpgradedPlayerCharacter::IsOnScreen(AActor* target, float Tolerance, FVector ViewPoint)
{
	bool bRecentlyRendered = target->WasRecentlyRendered(Tolerance);
	bool bLineOfSight = Controler->LineOfSightTo(target, ViewPoint, false);
	return (bRecentlyRendered && bLineOfSight);
}

void AUpgradedPlayerCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AUpgradedPlayerCharacter, ControlledBoids);
	DOREPLIFETIME(AUpgradedPlayerCharacter, OtherPlayers);
}