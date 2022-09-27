// Fill out your copyright notice in the Description page of Project Settings.


#include "GeneratedAsteroid.h"

// Sets default values
AGeneratedAsteroid::AGeneratedAsteroid()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = LocationComponent;
	LocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Location Component"));
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