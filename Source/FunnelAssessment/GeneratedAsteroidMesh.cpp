// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratedAsteroidMesh.h"

// Sets default values for this component's properties
UGeneratedAsteroidMesh::UGeneratedAsteroidMesh()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGeneratedAsteroidMesh::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGeneratedAsteroidMesh::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UGeneratedAsteroidMesh::SetupMesh(UProceduralMeshComponent* newMesh, int32 newSize, FVector localUp)
{
	this->Mesh = newMesh;
	this->Size = newSize;
	this->LocalZ = localUp;
	LocalX = FVector(LocalZ.Y, LocalZ.Z, LocalZ.X);
	LocalY = LocalZ.CrossProduct(LocalZ, LocalX);
}

void UGeneratedAsteroidMesh::ConstructMesh()
{
	//for (int32 Y = 0; Y < size; Y++)
	//{
	//	for (int32 X = 0; X < size; X++)
	//	{
	//		return;
	//	}
	//}

	Vertices.Add(FVector(0.0f, 0.0f, 0.0f));
	Vertices.Add(FVector(0.0f, 100.0f, 0.0f));
	Vertices.Add(FVector(100.0f, 100.0f, 0.0f));
	Vertices.Add(FVector(100.0f, 0.0f, 0.0f));

	Triangles.Add(0);
	Triangles.Add(1);
	Triangles.Add(3);
	Triangles.Add(3);
	Triangles.Add(1);
	Triangles.Add(2);

	UVCoords.Add(FVector2D(0.0f, 0.0f));
	UVCoords.Add(FVector2D(0.0f, 1.0f));
	UVCoords.Add(FVector2D(1.0f, 1.0f));
	UVCoords.Add(FVector2D(1.0f, 0.0f));

	Mesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(),	UVCoords, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
}
