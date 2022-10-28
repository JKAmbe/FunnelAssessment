// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "NewAsteroidFieldGenerator.generated.h"

UCLASS()
class FUNNELASSESSMENT_API ANewAsteroidFieldGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANewAsteroidFieldGenerator();
	//UPROPERTY(EditAnywhere)
		//UStaticMeshComponent* GeneratorArea;
	UPROPERTY(EditAnywhere)
		UBoxComponent* GeneratorArea;
	UPROPERTY(EditAnywhere)
		float AsteroidSize;
	UPROPERTY(EditAnywhere)
		float AsteroidSizeVariation;
	UPROPERTY(EditAnywhere)
		int AsteroidAmount;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AActor> Asteroid;
	TArray<AActor*> AsteroidList;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	UPROPERTY(EditAnywhere)
		bool bRegenerateMap;
	void GenerateAsteroidField();
};
