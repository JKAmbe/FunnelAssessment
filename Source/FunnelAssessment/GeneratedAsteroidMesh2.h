// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "GeneratedAsteroidMesh2.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUNNELASSESSMENT_API UGeneratedAsteroidMesh2 : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGeneratedAsteroidMesh2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	USceneComponent* LocationComponent;
	UProceduralMeshComponent* Mesh;
	int32 Size;
	FVector LocalUp;
	FVector LocalA;
	FVector LocalB;

	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVCoords;
	TArray<FVector> Normals;
	TArray<FProcMeshTangent> Tangents;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void SetupMesh(int32 newSize, FVector newUpDir);
	void GenerateMesh();
};
