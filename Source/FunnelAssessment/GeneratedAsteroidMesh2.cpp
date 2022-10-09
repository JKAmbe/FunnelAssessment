// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratedAsteroidMesh2.h"

// Sets default values for this component's properties
UGeneratedAsteroidMesh2::UGeneratedAsteroidMesh2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGeneratedAsteroidMesh2::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGeneratedAsteroidMesh2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// call from GeneratedAsteroid to set up new mesh
void UGeneratedAsteroidMesh2::SetupMesh(int32 newSize, FVector newUpDir)
{

	this->Size = newSize;
	this->LocalUp = newUpDir;
	this->LocalA = FVector(LocalUp.Y, LocalUp.Z, LocalUp.X);
	this->LocalB = LocalUp.CrossProduct(LocalUp, LocalA);
	UE_LOG(LogTemp, Warning, TEXT("Hi %i"), Size);

	GenerateMesh();
}

// use to generate mesh facing a direction
void UGeneratedAsteroidMesh2::GenerateMesh()
{
	Triangles.Empty();
	Vertices.Empty();
	UVCoords.Empty();
	Mesh->ClearAllMeshSections();

	//int32 i = 0;
	//for (int32 Y = 0; Y < Size; Y++)
	//{
	//	for (int X = 0; X < Size; X++)
	//	{
	//		// how much the current X and Y position is at relative to the size of cube
	//		FVector2D percent = FVector2D(X, Y) / (Size - 1);
	//		// add vertex
	//		//FVector VertexPoint = FVector((percent.X - 0.5f) * 2 * LocalA.X, (percent.Y - 0.5f) * 2 * LocalB.Y, LocalUp.Z);
	//		Vertices.Add(FVector(X * Size, Y * Size, 1));
	//		//Vertices.Add(VertexPoint);
	//		// add UV coordinates
	//		UVCoords.Add(FVector2D(X, Y));
	//		// add triangles
	//		if (X != Size - 1 && Y != Size - 1)
	//		{
	//			Triangles.Add(Y * Size + X);
	//			Triangles.Add((Y + 1) * Size + X);
	//			Triangles.Add(Y * Size + X + 1);
	//			Triangles.Add(Y * Size + X + 1);
	//			Triangles.Add((Y + 1) * Size + X);
	//			Triangles.Add((Y + 1) * Size + X + 1);
	//		}
	//		i++;
	//		UE_LOG(LogTemp, Warning, TEXT("%i"), i);
	//	}
	//}
	//// generate mesh
	//UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UVCoords, Normals, Tangents);
	//Mesh->CreateMeshSection(0, Vertices, Triangles, Normals, UVCoords, TArray<FColor>(), Tangents, true);

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

	Mesh->CreateMeshSection(0, Vertices, Triangles, TArray<FVector>(), UVCoords, TArray<FColor>(), TArray<FProcMeshTangent>(), true);
}