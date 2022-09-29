// Fill out your copyright notice in the Description page of Project Settings.


#include "AsteroidFieldGenerator.h"

// Sets default values
AAsteroidFieldGenerator::AAsteroidFieldGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LocationComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Location Component"));
	RootComponent = LocationComponent;
}

// Called when the game starts or when spawned
void AAsteroidFieldGenerator::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAsteroidFieldGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GenerateNewField)
	{
		ClearAsteroidField();
		SpawnAsteroidField();
		GenerateNewField = false;
	}
}

bool AAsteroidFieldGenerator::ShouldTickIfViewportsOnly() const
{
	return true;
}

void AAsteroidFieldGenerator::ClearAsteroidField()
{
	//for (auto i : Asteroids)
	//{
	//	i->Destroy();
	//}
	//auto ClassName = Asteroids[0]->GetClass()->GetName();
	//for (TActorIterator<ClassName> It(GetWorld()); It; ++It)
	//{
	//	(*It)->Destroy();
	//}
	//Asteroids.Empty();
	for (int32 i = 0; i < Asteroids.Num(); i++)
	{
		Asteroids[i]->Destroy();
	}
	Asteroids.Empty();
}

void AAsteroidFieldGenerator::SpawnAsteroidField()
{
	// place a asteroid point for each width and height

	float PerlinOffset = FMath::RandRange(-10000.0f, 10000.0f);

	if (GenerationType == EGenerationType::Normal)
	{
		for (int y = 0; y < AsteroidFieldY; y++)
		{
			for (int x = 0; x < AsteroidFieldX; x++)
			{
				// For each point, get the noise and calculate how much asteroid it should spawn 
				int SpawnAmt = FMath::Lerp(1, AsteroidDensity, FMath::PerlinNoise2D(FVector2D(x * PerlinRoughness + PerlinOffset, y * PerlinRoughness + PerlinOffset)));
				float PointMaxHeight = SpaceBetween * SpawnAmt;
				float BaseHeight = (PointMaxHeight / 2) * -1;
				// Distribute the asteroid equally
				for (int i = 0; i < SpawnAmt; i++)
				{
					// starting from -MaxHeight, set Z as i * SpaceBetween and Spawn a asteroid point
					float AsteroidPointZ = BaseHeight + (i * SpaceBetween);
					auto newAsteroid = GetWorld()->SpawnActor<AActor>(AsteroidToSpawn, this->GetActorLocation() + FVector(x * SpaceBetween, y * SpaceBetween, AsteroidPointZ), this->GetActorRotation() + FRotator(), FActorSpawnParameters());
					Asteroids.Add(newAsteroid);
				}
			}
		}
	}
	if (GenerationType == EGenerationType::CenterWeighted)
	{
		int32 CenterY = AsteroidFieldY / 2 + 1;
		int32 CenterX = AsteroidFieldX / 2 + 1;
		for (int y = 0; y < AsteroidFieldY; y++)
		{

			for (int x = 0; x < AsteroidFieldX; x++)
			{
				float Weight;
				//float WeightMod;
				if (x == CenterX)
				{
					Weight = 1.0f;

				}
				else
				// lower the weight the furter it is away from the center
				{
					if (x < CenterX)
					{
						Weight = FMath::Lerp(0.0f, 1.0f, (float(x) / (float(CenterX) - 1.0f)));
					}
					if (x > CenterX)
					{
						Weight = FMath::Lerp(1.0f, 0.0f, ((float(x) - float(CenterX)) / float(CenterX)));
					}
				}
				//if (y == CenterY)
				//{
				//	Weight = 1.0;
				//}
				//if (y < CenterY)
				//{
				//	WeightMod = FMath::Lerp(0.1f, 1.0f, (float(y) / (float(CenterY) - 1.0f)));
				//	Weight = WeightMod;
				//}
				//if (y > CenterY)
				//{
				//	WeightMod = FMath::Lerp(1.0f, 0.1f, ((float(y) - float(CenterY)) / float(CenterY)));
				//	Weight = WeightMod;
				//}
				//{
				//	if (x < CenterX)
				//	{
				//		Weight = FMath::Lerp(0.1f, 1.0f, (float(x) / (float(CenterX) - 1.0f)));
				//		//if (y < CenterY)
				//		//{
				//		//	WeightMod = FMath::Lerp(0.1f, 1.0f, (float(y) / (float(CenterY) - 1.0f)));
				//		//	Weight -= WeightMod;
				//		//}
				//		//if (y > CenterY)
				//		//{
				//		//	WeightMod = FMath::Lerp(1.0f, 0.1f, ((float(y) - float(CenterY)) / float(CenterY)));
				//		//	Weight -= WeightMod;
				//		//}
				//		//UE_LOG(LogTemp, Error, TEXT("%f %f"), Weight, WeightMod);
				//	}
				//}
				//{
				//	if (x < CenterX)
				//	{
				//		Weight = FMath::Lerp(0.1f, 1.0f, (float(x) / (float(CenterX) - 1.0f)));
				//		if (y < CenterY)
				//		{
				//			WeightMod = FMath::Lerp(0.1f, 1.0f, (float(y) / (float(CenterY) - 1.0f)));
				//			Weight -= WeightMod;
				//		}
				//		if (y > CenterY)
				//		{
				//			WeightMod = FMath::Lerp(1.0f, 0.1f, ((float(y) - float(CenterY)) / float(CenterY)));
				//			Weight -= WeightMod;
				//		}
				//	}
				//	if (x > CenterX)
				//	{
				//		Weight = FMath::Lerp(1.0f, 0.1f, ((float(x) - float(CenterX)) / float(CenterX)));
				//		if (y < CenterY)
				//		{
				//			WeightMod = FMath::Lerp(0.1f, 1.0f, (float(y) / (float(CenterY) - 1.0f)));
				//			Weight -= WeightMod;
				//		}
				//		if (y > CenterY)
				//		{
				//			WeightMod = FMath::Lerp(1.0f, 0.1f, ((float(y) - float(CenterY)) / float(CenterY)));
				//			Weight -= WeightMod;
				//		}
				//	}
				//}

				// set Spawn amount
				float SpawnAmt = float(AsteroidDensity) * Weight;
				// use noise to change the spawnAmt
				SpawnAmt = FMath::Lerp(0.0f, SpawnAmt, FMath::PerlinNoise2D(FVector2D(x * PerlinRoughness + PerlinOffset, y * PerlinRoughness + PerlinOffset)));
				float PointMaxHeight = SpaceBetween * SpawnAmt;
				float BaseHeight = (PointMaxHeight / 2) * -1;

				// Spawn the asteroids
				for (int i = 0; i < int(SpawnAmt); i++)
				{
					// starting from -MaxHeight, set Z as i * SpaceBetween and Spawn a asteroid point
					float AsteroidPointZ = BaseHeight + (i * SpaceBetween);
					auto newAsteroid = GetWorld()->SpawnActor<AActor>(AsteroidToSpawn, this->GetActorLocation() + FVector(x * SpaceBetween, y * SpaceBetween, AsteroidPointZ), this->GetActorRotation() + FRotator(), FActorSpawnParameters());
					Asteroids.Add(newAsteroid);
				}
			}
		}
	}
}
