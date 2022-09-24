// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidPoint.h"

// Sets default values
AAsteroidPoint::AAsteroidPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Location Component"));
	RootComponent = LocationComponent;
}

// Called when the game starts or when spawned
void AAsteroidPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAsteroidPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

