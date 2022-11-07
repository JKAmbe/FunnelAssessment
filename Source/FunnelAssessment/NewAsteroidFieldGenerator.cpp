// Fill out your copyright notice in the Description page of Project Settings.


#include "NewAsteroidFieldGenerator.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"


// Sets default values
ANewAsteroidFieldGenerator::ANewAsteroidFieldGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bRegenerateMap = false;
	//GeneratorArea = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Generator Area"));
	GeneratorArea = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
}

// Called when the game starts or when spawned
void ANewAsteroidFieldGenerator::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ANewAsteroidFieldGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bRegenerateMap == true)
	{
		//do something here
		GenerateAsteroidField();
		bRegenerateMap = false;
	}
}

bool ANewAsteroidFieldGenerator::ShouldTickIfViewportsOnly() const
{
	return true;
}

void ANewAsteroidFieldGenerator::GenerateAsteroidField()
{
	//FlushPersistentDebugLines(GetWorld());
	for (AActor* StoredAsteroid : AsteroidList)
	{
		StoredAsteroid->Destroy();
	}
	AsteroidList.Empty();

	//UE_LOG(LogTemp, Warning, TEXT("%s"), *GeneratorArea->GetScaledBoxExtent().ToString())
	for (int i = 0; i <= AsteroidAmount; i++) {
		FVector RandPoint = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), GeneratorArea->GetScaledBoxExtent());
		if (Asteroid) {
			
			AActor* tmp = GetWorld()->SpawnActor<AActor>(Asteroid, RandPoint, UKismetMathLibrary::RandomRotator());
			tmp->SetActorScale3D(FVector(AsteroidSize) + FVector(FMath::RandRange(-AsteroidSizeVariation, AsteroidSizeVariation),
				FMath::RandRange(-AsteroidSizeVariation, AsteroidSizeVariation), FMath::RandRange(-AsteroidSizeVariation, AsteroidSizeVariation)));
			//tmp->SetActorScale3D(FVector(FMath::RandRange(1.0f, 10.0f), FMath::RandRange(1.0f, 10.0f), FMath::RandRange(1.0f, 10.0f)));
			AsteroidList.Add(tmp);
		}
			
		//DrawDebugPoint(GetWorld(), RandPoint, 10.0f, FColor::Blue, true, -1.0f, 8);
	}
}

