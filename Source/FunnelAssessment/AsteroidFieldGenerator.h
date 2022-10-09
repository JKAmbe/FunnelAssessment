// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GeneratedAsteroid.h"
#include "EngineUtils.h"
#include "AsteroidPoint.h"
#include "AsteroidFieldGenerator.generated.h"

UENUM()
enum class EGenerationType : uint8
{
	Normal,
	CenterWeighted,
};

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
	UPROPERTY(EditAnywhere)
		bool GenerateNewField = false;

	UPROPERTY(EditAnywhere, Category = "Asteroid Field Generation Setting")
		EGenerationType GenerationType = EGenerationType::Normal;
	UPROPERTY(EditAnywhere, Category="Asteroid Field Generation Setting")
		int32 AsteroidFieldX = 10;
	UPROPERTY(EditAnywhere, Category = "Asteroid Field Generation Setting")
		int32 AsteroidFieldY = 10;
	UPROPERTY(EditAnywhere, Category="Asteroid Field Generation Setting")
		float SpaceBetween = 500.0;
	UPROPERTY(EditAnywhere, Category = "Asteroid Field Generation Setting")
		int32 AsteroidDensity = 12;
	UPROPERTY(EditAnywhere, Category = "Asteroid Field Generation Setting")
		float PerlinRoughness = 0.001;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> Asteroids;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	void ClearAsteroidField();
	void SpawnAsteroidField();

};
