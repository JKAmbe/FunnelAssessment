// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlayerController3DM.h"
#include "Boids.h"
#include "Net/UnrealNetwork.h"
#include "UpgradedPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class FUNNELASSESSMENT_API AUpgradedPlayerCharacter : public APlayerController3DM
{
	GENERATED_BODY()
	
	//overrides
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void Tick(float Del) override;
public:
	//Custom Event
	//AUpgradedPlayerCharacter::AUpgradedPlayerCharacter();
	UFUNCTION(Server, Reliable)
		void ChangeOwnership(ABoids* Boid);
	UFUNCTION(Server, Reliable)
		void SetFollowTarget(bool bCanSee, AUpgradedPlayerCharacter* Caller);
	UFUNCTION(NetMulticast, Reliable)
		void UpdateUIOverride(AUpgradedPlayerCharacter* Caller, ABoids* boid);
	UFUNCTION()
		void LockedOn(ABoids* Boid);
	TScriptDelegate <FWeakObjectPtr> LockedOnDG;

	//Properties

		TArray<ABoids*> Boids;
	UPROPERTY(Replicated)
		TArray<ABoids*> ControlledBoids;
	UPROPERTY(Replicated)
		TArray<AUpgradedPlayerCharacter*> OtherPlayers;
	UPROPERTY(BlueprintReadWrite)
		UWidgetComponent* MarkerComponent;
	AController* Controler;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
	//helper Method
	void UpdateOtherPlayerContent();
	void BoidsVisibilityCheck();
	void EnemyVisibilityCheck();
	bool IsOnScreen(AActor* target, float Tolerance = 0.1f, FVector ViewPoint = FVector(0, 0, 0));
};
