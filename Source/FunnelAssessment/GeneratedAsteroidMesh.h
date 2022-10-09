// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "ProceduralMeshComponent.h"
#include "GeneratedAsteroidMesh.generated.h"

// OLD CLASS
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUNNELASSESSMENT_API UGeneratedAsteroidMesh : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGeneratedAsteroidMesh();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UProceduralMeshComponent* Mesh;

	int32 Size;
	FVector LocalZ;
	FVector LocalX;
	FVector LocalY;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVCoords;
	TArray<FVector> Normals;
	TArray<FProcMeshTangent> Tangents;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupMesh(UProceduralMeshComponent* newMesh, int32 newSize, FVector localUp);
	void ConstructMesh();
};
