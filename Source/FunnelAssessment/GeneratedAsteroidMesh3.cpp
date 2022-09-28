// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratedAsteroidMesh3.h"

// Sets default values
AGeneratedAsteroidMesh3::AGeneratedAsteroidMesh3()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	Mesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Mesh Component"));
}

// Called when the game starts or when spawned
void AGeneratedAsteroidMesh3::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AGeneratedAsteroidMesh3::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGeneratedAsteroidMesh3::SetupMesh(int32 newSize, FVector newUpDir, UMaterial* newMaterial)
{

	this->Size = newSize;
	this->LocalUp = newUpDir;
	this->LocalA = FVector(LocalUp.Y, LocalUp.Z, LocalUp.X);
	this->LocalB = LocalUp.CrossProduct(LocalUp, LocalA);
	UE_LOG(LogTemp, Warning, TEXT("Hi %i"), Size);
	Material = newMaterial;
	GenerateMesh();
}

// use to generate mesh facing a direction
void AGeneratedAsteroidMesh3::GenerateMesh()
{
	Triangles.Empty();
	Vertices.Empty();
	UVCoords.Empty();
	Mesh->ClearAllMeshSections();

	int32 i = 0;
	float PerlinOffset = FMath::RandRange(-10000.0f, 10000.0f);

	for (int32 Y = 0; Y < Size; Y++)
	{
		for (int32 X = 0; X < Size; X++)
		{
			// how much the current X and Y position is at relative to the size of cube
			FVector2D percent = FVector2D(X, Y) / (Size - 1);
			// add vertex
			//FVector VertexPoint = FVector((percent.X - 0.5f) * 2 * LocalA.X, (percent.Y - 0.5f) * 2 * LocalB.Y, LocalUp.Z);
			//Vertices.Add(FVector(X * Size, Y * Size, 1));
			FVector VertexPoint = (LocalUp + (percent.X - .5f) * 2 * LocalA + (percent.Y - .5f) * 2 * LocalB);
			VertexPoint.Normalize();
			// upscale verterx 
			VertexPoint *= Size * BaseTriangleSize;
			// if the vertex is not at the edge, make it look chunky
			FVector AVertexPoint = VertexPoint;
			if (!(X+1 == Size || X == 0) || !(Y+1 == Size || Y == Size))
			{			
				// use noise to offset the vertex point
				// make it look more asteroidy
				// Chunky round asteroids
				//float PerlinRoughness = FMath::RandRange(0.05, 0.6f);
				float PerlinRoughness = 0.05;
				AVertexPoint.Z = VertexPoint.Z + VertexPoint.Z * (FMath::PerlinNoise3D(FVector(X * PerlinRoughness + PerlinOffset, Y * PerlinRoughness + PerlinOffset, VertexPoint.Z * PerlinRoughness + PerlinOffset)));
				AVertexPoint.Y = VertexPoint.Y + VertexPoint.Y * (FMath::PerlinNoise3D(FVector(X * PerlinRoughness + PerlinOffset, VertexPoint.Y * PerlinRoughness + PerlinOffset, VertexPoint.Z * PerlinRoughness + PerlinOffset)));
				AVertexPoint.X = VertexPoint.X + VertexPoint.X * (FMath::PerlinNoise3D(FVector(VertexPoint.X * PerlinRoughness + PerlinOffset, Y * PerlinRoughness + PerlinOffset, VertexPoint.Z * PerlinRoughness + PerlinOffset)));
			}
			// if not set to normal
			else
			{
				AVertexPoint = VertexPoint;
			}

			Vertices.Add(AVertexPoint);
			// add UV coordinates
			UVCoords.Add(FVector2D(X, Y));
			// add triangles
			if (X != Size - 1 && Y != Size - 1)
			{
				Triangles.Add(Y * Size + X);
				Triangles.Add((Y + 1) * Size + X);
				Triangles.Add(Y * Size + X + 1);
				Triangles.Add(Y * Size + X + 1);
				Triangles.Add((Y + 1) * Size + X);
				Triangles.Add((Y + 1) * Size + X + 1);
			}
			i++;
		}
	}
	// generate mesh
	UKismetProceduralMeshLibrary::CalculateTangentsForMesh(Vertices, Triangles, UVCoords, Normals, Tangents);
	Mesh->CreateMeshSection(0, Vertices, Triangles, Normals, UVCoords, TArray<FColor>(), Tangents, true);

	// Apply material
	Mesh->SetMaterial(0, Material);

}