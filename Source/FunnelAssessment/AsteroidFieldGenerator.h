// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidPoint.h"
#include "AsteroidFieldGenerator.generated.h"

UCLASS()
class FUNNELASSESSMENT_API AAsteroidFieldGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidFieldGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:
	USceneComponent* LocationComponent;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AActor> AsteroidToSpawn;

	UPROPERTY(EditAnywhere, Category="Asteroid Field Generation")
		int32 AsteroidFieldX = 10;
	UPROPERTY(EditAnywhere, Category = "Asteroid Field Generation")
		int32 AsteroidFieldY = 10;
	UPROPERTY(EditAnywhere, Category="Asteroid Field Generation")
		float SpaceBetween = 500.0;
	UPROPERTY(EditAnywhere, Category = "Asteroid Field Generation")
		int32 MaxAsteroidPerPoint = 24;
	UPROPERTY(EditAnywhere, Category = "Asteroid Field Generation")
		float PerlinScale;
	UPROPERTY(EditAnywhere, Category = "Asteroid Field Generation")
		float PerlinRoughness;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SpawnPointer();

};
