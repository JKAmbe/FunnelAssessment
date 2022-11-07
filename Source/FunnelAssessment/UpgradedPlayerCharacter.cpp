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

	//essentially just to populate its own variable
	//get all boids in scene and bind this object so it listens when Locked on is called
	for (TActorIterator<ABoids> It(GetWorld()); It; ++It) {
		Boids.Add(*It);
		LockedOnDG.BindUFunction(this, "LockedOn");
		((ABoids*)(*It))->LockedOn.Add(LockedOnDG);
	}
	//get own widget component (marker)
	MarkerComponent = FindComponentByClass<UWidgetComponent>();
	UMarker* MarkerWidget = (UMarker*)MarkerComponent->GetWidget();
	//getController
	if (GetController())
		Controler = GetController();

	bReplicates = true;
}

void AUpgradedPlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	//when a new playeer enters the server, update all 'other player' variable
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
/// <summary>
/// Call in server to update 'controlled boids' on all playercharacter, as in remove the boid from the old owner's list of controlled boids, and add it to the new owner
/// </summary>
void AUpgradedPlayerCharacter::ChangeOwnership_Implementation(ABoids* Boid)
{
	for (AUpgradedPlayerCharacter* Enemy : OtherPlayers)
		if (Enemy)
		{
			Enemy->ControlledBoids.Remove(Boid);
			UpdateUIOverride(this, Boid);
		}
	ControlledBoids.AddUnique(Boid);
}
/// <summary>
/// <para>Callback to server, When playercan see a target, they'd want to change the follow target of the boid				</para>
/// <para>they'll call this server function so server will update it on iself and all clients through method replicaiton	</para>
/// </summary>
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
/// <summary>
/// <para>Multicast call, Essentially 'reset' the markers hud when a boid change ownership</para>
/// <para>Animation Resetting happens in MarkerBP</para>
/// </summary>
void AUpgradedPlayerCharacter::UpdateUIOverride_Implementation(AUpgradedPlayerCharacter* Caller, ABoids* Boid)
{		
	if (Caller->GetLocalRole() == ROLE_SimulatedProxy)
		for (ABoids* boid : ControlledBoids)
			((UMarker*)boid->MarkerComponent->GetWidget())->Reset();
}

/// <summary>
/// Binded into BOid's Locked on, When boid is locked on, Call Cahneg ownership in server
/// </summary>
void AUpgradedPlayerCharacter::LockedOn(ABoids* Boid)
{
	if (GetLocalRole() == ROLE_AutonomousProxy)
		ChangeOwnership(Boid);
}

/// <summary>
/// Helper method to update 'otherPlayers' variable in each player
/// </summary>
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

/// <summary>
/// check whether each boids is visible in player view
/// </summary>
void AUpgradedPlayerCharacter::BoidsVisibilityCheck()
{
	for (ABoids* boid : Boids)
		boid->MarkerComponent->SetVisibility(ControlledBoids.Contains(boid) || IsOnScreen(boid));
}

/// <summary>
/// check whether each otehr player is visible in player view
/// </summary>
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

/// <summary>
/// helper method consisting of WasRecentlyRendered and LineOfSight
/// </summary>
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