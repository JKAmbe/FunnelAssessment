// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Boids.h"
#include "PlayerController3DM.generated.h"

UCLASS()
class FUNNELASSESSMENT_API APlayerController3DM : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerController3DM();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	// Movement functions
	void SetMovementMode();
	UFUNCTION(Server, Reliable)
		void ServerSetMovementMode();

	void MoveForward(float val);
	void Strafe(float val);
	void MoveVertical(float val);
	void LookX(float val);
	void LookY(float val);

	void BoostCheck();
	void BoostCheck2();
	void BoostOn();
	UFUNCTION(Server, Reliable)
		void ServerBoostOn();
	void BoostOff();
	UFUNCTION(Server, Reliable)
		void ServerBoostOff();

	UFUNCTION(Server, Reliable)
		void ServerTest();

	// Player ability/feature functions
	void SpawnFunnels();

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Player movement and boost
	UPROPERTY(EditAnywhere)
		float FlySpeed = 1000.0f;
	UPROPERTY(EditAnywhere)
		float FlyDeceleration = 2000.0f;
	UPROPERTY(EditAnywhere)
		float BoostMultiplier = 2.0f;
	UPROPERTY(EditAnywhere)
		float MaxBoostDuration = 2.0f;

	// Set the funnel class, the amount to spawn and the target they should be chasing
	UPROPERTY(EditAnywhere)
		TSubclassOf<ABoids> FunnelClass;
	UPROPERTY(EditAnywhere)
		int FunnelAmt = 5;
	UPROPERTY(EditAnywhere)
		AActor* FunnelTarget;
	TArray<ABoids*> Funnels;

private:
	UCameraComponent* Camera;
	UCharacterMovementComponent* MoveComponent;

	UPROPERTY(Replicated)
		bool bBoostActive = false;
	float bBoostCooldown = false;
	float BoostTime = 0.0f;
	float BoostCooldown = 1.0f;
	float FunnelOffset = 500.0f;
	float BoostSpeed;
};
