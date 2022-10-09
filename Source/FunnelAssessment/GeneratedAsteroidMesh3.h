// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "GeneratedAsteroidMesh3.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FUNNELASSESSMENT_API AGeneratedAsteroidMesh3 : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneratedAsteroidMesh3();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UProceduralMeshComponent* Mesh;

	UMaterial* Material;

	int32 Size;
	int32 BaseTriangleSize = 10;
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
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetupMesh(int32 newSize, FVector newUpDir, UMaterial* newMaterial);
	void GenerateMesh();
};
