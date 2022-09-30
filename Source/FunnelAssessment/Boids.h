// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EngineUtils.h"
#include "Boids.generated.h"

UCLASS()
class FUNNELASSESSMENT_API ABoids : public ACharacter
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABoids();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void MoveForward();
	void Separation(float dt, TArray<ABoids*> LocalBoids, float Strength);
	void Alignment(float dt, TArray<ABoids*> LocalBoids, float Strength);
	void Cohesion(float dt, TArray<ABoids*> LocalBoids, float Strength);
	void FlyToTarget(float dt, FVector target, float Strength);
	void AvoidCollision(float dt, float Strength);
	UPROPERTY(EditAnywhere)
		float LocalRadius;
	UPROPERTY(EditAnywhere)
		AActor* FollowTarget;
	UPROPERTY(EditAnywhere, meta = (UIMin = 0.0f, UIMax = 180.0f, NoSpinbox = false))
		float MaxAngle;

	UPROPERTY(EditAnywhere, meta=( UIMin = 1.0f, UIMax = 200.0f, ClampMin = 1.0f,NoSpinbox = false))
		float SeperationStrength;
	UPROPERTY(EditAnywhere, meta = (UIMin = 1.0f, UIMax = 200.0f, ClampMin = 1.0f, NoSpinbox = false))
		float AlignmentStrength;
	UPROPERTY(EditAnywhere, meta = (UIMin = 1.0f, UIMax = 200.0f, ClampMin = 1.0f, NoSpinbox = false))
		float CohesionStrength;

	UPROPERTY(EditAnywhere, meta = (UIMin = 0.0f, UIMax = 5.0f, NoSpinbox = false))
		float FollowStrength;
	UPROPERTY(EditAnywhere, meta = (UIMin = 0.0f, UIMax = 5.0f, NoSpinbox = false))
		float CollisionAvoidanceStrength;
	UPROPERTY(EditAnywhere, meta = (UIMin = 0.0f, UIMax = 1000.0f, NoSpinbox = false))
		float AvoidanceDistanceRange;
	void RotateToDirection(float dt, FVector direction, float Strength);
	void GetAllBoids();
	TArray<ABoids*> AllBoids;
};
