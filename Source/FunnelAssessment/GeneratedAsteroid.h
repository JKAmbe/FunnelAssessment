// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "GeneratedAsteroidMesh3.h"
#include "GeneratedAsteroid.generated.h"

UCLASS()
class FUNNELASSESSMENT_API AGeneratedAsteroid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneratedAsteroid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	USceneComponent* LocationComponent;
	//UPROPERTY(VisibleAnywhere)
	//	TArray<UProceduralMeshComponent*> PCGMeshes;
	//UPROPERTY(VisibleAnywhere)
	//	TArray<UGeneratedAsteroidMesh2*> GeneratedAsteroidMeshes;
	//UPROPERTY(VisibleAnywhere)
	//	TArray<UGeneratedAsteroidMesh2*> GeneratedAsteroidMeshes;

	UPROPERTY(VisibleAnywhere)
		TArray<AGeneratedAsteroidMesh3*> GeneratedAsteroidMeshes;
	int32 Size = 5;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void GenerateAsteroidMesh();

};
