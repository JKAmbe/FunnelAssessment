// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratedAsteroid.h"

// Sets default values
AGeneratedAsteroid::AGeneratedAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = LocationComponent;
	LocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Location Component"));
	GenerateAsteroidMesh();

	//MeshComponent = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Mesh Component"));
	//AsteroidMesh = CreateDefaultSubobject<UGeneratedAsteroidMesh>(TEXT("Asteroid Mesh Component"));
	//if (AsteroidMesh != nullptr)
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Generating mesh on load"));
	//	AsteroidMesh->SetupMesh(MeshComponent, 5, FVector(0, 0, 1));
	//	AsteroidMesh->ConstructMesh();
	//}
}

// Called when the game starts or when spawned
void AGeneratedAsteroid::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGeneratedAsteroid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGeneratedAsteroid::GenerateAsteroidMesh()
{
	// lol
	//for (int32 i = 0; i < 6; i++)
	//{
	//	FString GAMName = FString("Generated Asteroid Mesh ");
	//	GAMName.Append(FString::FromInt(i));
	//	AGeneratedAsteroidMesh3* newGenAsteroid = CreateDefaultSubobject<AGeneratedAsteroidMesh3>(*GAMName);
	//	newGenAsteroid->SetupAttachment(RootComponent);
	//}

	//UE_LOG(LogTemp, Warning, TEXT("HELL O SIR ARE YOU AWAKE??"));
	//GeneratedAsteroidMeshes.Empty();
	//for (int32 i = 0; i < 6; i++)
	//{
	//	//FString GAMName = FString("Generated Asteroid Mesh ");
	//	//GAMName.Append(FString::FromInt(i));
	//	//UGeneratedAsteroidMesh2* newGenAsteroid = CreateDefaultSubobject<UGeneratedAsteroidMesh2>(*GAMName);
	//	//GeneratedAsteroidMeshes.Add(newGenAsteroid);
	//	//newGenAsteroid->SetupAttachment(RootComponent);
	//	//newGenAsteroid->SetupMesh(Size, FVector(0, 0, 1));
	//}

	//PCGMeshes.Empty();
	//GeneratedAsteroidMeshes.Empty();
	//for (int32 i = 0; i < 6; i++)
	//{
	//	FString PCGMeshName = FString("PCGMesh ");
	//	PCGMeshName.Append(FString::FromInt(i));
	//	UProceduralMeshComponent* newMesh = CreateDefaultSubobject<UProceduralMeshComponent>(*PCGMeshName);
	//	PCGMeshes.Add(newMesh);

	//	FString GAMName = FString("Generated Asteroid Mesh ");
	//	GAMName.Append(FString::FromInt(i));
	//	UGeneratedAsteroidMesh2* newGenAsteroid = CreateDefaultSubobject<UGeneratedAsteroidMesh2>(*GAMName);
	//	GeneratedAsteroidMeshes.Add(newGenAsteroid);

	//	newGenAsteroid->SetupMesh(newMesh, Size, FVector(0, 0, 1));
	//}	
}
