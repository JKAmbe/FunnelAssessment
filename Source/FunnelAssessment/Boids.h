// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EngineUtils.h"
#include "Particles/ParticleSystemComponent.h"
#include "Boids.generated.h"

UCLASS()
class FUNNELASSESSMENT_API ABoids : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoids();
	float MaxFlySpeedTMP;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void MoveForward();
	void Separation(float dt, TArray<ABoids*> LocalBoids, float Strength, FVector CurrentLocation);
	void Alignment(float dt, TArray<ABoids*> LocalBoids, float Strength, FVector CurrentLocation);
	void Cohesion(float dt, TArray<ABoids*> LocalBoids, float Strength, FVector CurrentLocation);
	void FlyToTarget(float dt, FVector target, float Strength, FVector CurrentLocation);
	void AvoidCollision(float dt, float Strength, FVector CurrentLocation);
	UPROPERTY(EditAnywhere)
		float LocalRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USoundBase* BeamSound;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		AActor* FollowTarget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bFireable;
	UPROPERTY(EditAnywhere, meta = (UIMin = 0.0f, UIMax = 5.0f, NoSpinbox = false))
		float UntilNextFire;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=( UIMin = 1.0f, UIMax = 200.0f, ClampMin = 1.0f,NoSpinbox = false))
		float SeperationStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 1.0f, UIMax = 200.0f, ClampMin = 1.0f, NoSpinbox = false))
		float AlignmentStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite,  meta = (UIMin = 1.0f, UIMax = 200.0f, ClampMin = 1.0f, NoSpinbox = false))
		float CohesionStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0.0f, UIMax = 5.0f, NoSpinbox = false))
		float FollowStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (UIMin = 0.0f, UIMax = 5.0f, NoSpinbox = false))
		float CollisionAvoidanceStrength;
	UPROPERTY(EditAnywhere, meta = (UIMin = 0.0f, UIMax = 1000.0f, NoSpinbox = false))
		float AvoidanceDistanceRange;
	void RotateToDirection(float dt, FVector direction, float Strength);
	void GetAllBoids();
	void FireSequence(FVector CurrentLocation, FVector target);
	TArray<ABoids*> AllBoids;
	UPROPERTY(BlueprintReadWrite)
		UParticleSystemComponent* BeamParticle;
};
