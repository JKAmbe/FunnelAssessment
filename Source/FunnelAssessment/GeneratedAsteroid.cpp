// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratedAsteroid.h"

// Sets default values
AGeneratedAsteroid::AGeneratedAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Spawns a mesh component as its root
	RootComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Root Component"));
	RootComponent = RootComponent;
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


// Sets Size var as random size between the base and max size
int32 AGeneratedAsteroid::RandomSize(int newSize)
{
	return Size = FMath::RandRange(BaseSize, MaxSize);
}

// Randomly scale the size of the asteroid based on the Size var
void AGeneratedAsteroid::RandomScale()
{
	this->SetActorScale3D(FVector(FMath::RandRange(1, 1 + Size / MaxSize), FMath::RandRange(1, 1 + Size / MaxSize), FMath::RandRange(1, 1 + Size / MaxSize)));
}