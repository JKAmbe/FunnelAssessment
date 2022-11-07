// Fill out your copyright notice in the Description page of Project Settings.


#include "Boids.h"
#include "Math/RotationMatrix.h"
#include "DrawDebugHelpers.h"
#include "Math/UnrealMathUtility.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Runtime/AIModule/Classes/AIController.h"
#include "AIController.h"
#include "HealthComponent.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/CharacterMovementComponent.h"


// Sets default values
ABoids::ABoids()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	LocalRadius = 1000.0f;
	SeperationStrength = 1.0f;
	AlignmentStrength = 5.0f;
	CohesionStrength = 5.0f;
	FollowStrength = 20.0f;
	FireDuration = 0.1f;
	CollisionAvoidanceStrength = 200.0f;

	bReplicates = true;
}

// Called when the game starts or when spawned
void ABoids::BeginPlay()
{
	Super::BeginPlay();
	SpawnDefaultController();
	//UE_LOG(LogTemp, Warning, TEXT("tests"))
	GetAllBoids();
	MaxFlySpeedTMP = GetCharacterMovement()->MaxFlySpeed;


	//new stufff
	MarkerComponent = FindComponentByClass<UWidgetComponent>();
	UMarker* MarkerWidget = (UMarker*)MarkerComponent->GetWidget();

	TargettedDG.BindUFunction(this, "Targetted");//bind delegate to function (i.e. the redline going backward in BP)
	MarkerWidget->OnMarked.Add(TargettedDG);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *TargettedDG.GetFunctionName().ToString()));
}

// Called every frame
void ABoids::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	TArray <ABoids*> LocalBoids;
	FVector CurrentPosition = GetActorLocation();
	for (ABoids* boid : AllBoids)
	{
		if (boid)
		{
			FVector RelativePosition = boid->GetActorLocation() - CurrentPosition;
			float Angle = FMath::RadiansToDegrees(acosf(FVector::DotProduct(GetActorForwardVector(), RelativePosition.GetSafeNormal())));
			if (RelativePosition.IsNearlyZero(LocalRadius) && Angle <= 30)
				LocalBoids.Add(boid);
		}

	}
	//base boids behaviour, Seperation, Alignement, Cohesion
	/*Separation(DeltaTime, LocalBoids, bFireable? SeperationStrength : 1.0f, CurrentPosition);
	Alignment(DeltaTime, LocalBoids, bFireable ? AlignmentStrength : 1.0f, CurrentPosition);
	Cohesion(DeltaTime, LocalBoids, bFireable ? CohesionStrength : 1.0f, CurrentPosition);*/

	Separation(DeltaTime, LocalBoids, SeperationStrength, CurrentPosition);
	Alignment(DeltaTime, LocalBoids, AlignmentStrength, CurrentPosition);
	Cohesion(DeltaTime, LocalBoids,  CohesionStrength, CurrentPosition);

	//Obstacle Avoidance and target follow
	if (FollowTarget)
	{
		FlyToTarget(DeltaTime, FollowTarget->GetActorLocation(), bFireable ? FollowStrength:1.0f, CurrentPosition);
		if ((FollowTarget->GetActorLocation() - CurrentPosition).IsNearlyZero(LocalRadius) && bFireable == true) {
			FireSequence(CurrentPosition, FollowTarget->GetActorLocation());
		}
	}
		
	AvoidCollision(DeltaTime, CollisionAvoidanceStrength, CurrentPosition);
	//AvoidCollision(DeltaTime, bFireable ? CollisionAvoidanceStrength : 1.0f, CurrentPosition);
	//Move forward, Direction(rotation) is decided by other behaviour
	MoveForward();
	//UE_LOG(LogTemp,Warning, TEXT("%f"), (float)bFireable)
}

void ABoids::MoveForward()
{
	AddMovementInput(GetActorForwardVector()*100.0f);
	
}

void ABoids::Separation(float dt, TArray<ABoids*> LocalBoids, float Strength, FVector CurrentLocation)
{
	for (ABoids* boid : LocalBoids) {
		FVector oppositeOfBoid = -(boid->GetActorLocation() - CurrentLocation) + CurrentLocation;
		RotateToDirection(dt, oppositeOfBoid, Strength);
	}
}

void ABoids::Alignment(float dt, TArray<ABoids*> LocalBoids, float Strength, FVector CurrentLocation)
{
	FVector AverageDirection = FVector(0, 0, 0);
	for (ABoids* boid : LocalBoids)
		AverageDirection += (boid->GetActorForwardVector());
	AverageDirection = AverageDirection / LocalBoids.Num();
	
	if (LocalBoids.Num() > 0)
		RotateToDirection(dt, CurrentLocation + AverageDirection, Strength);
		
}

void ABoids::Cohesion(float dt, TArray<ABoids*> LocalBoids, float Strength, FVector CurrentLocation)
{
	FVector AveragePosition = FVector(0, 0, 0);
	for (ABoids* boid : LocalBoids)
		AveragePosition += boid->GetActorLocation();
	AveragePosition += CurrentLocation;
	if (LocalBoids.Num() > 0) {
		AveragePosition = AveragePosition / (LocalBoids.Num()+1);
		RotateToDirection(dt, AveragePosition, Strength);
	}
}

void ABoids::FlyToTarget(float dt, FVector target, float Strength, FVector CurrentLocation)
{
	RotateToDirection(dt,  target, Strength);
}

void ABoids::AvoidCollision(float dt, float Strength, FVector CurrentLocation)
{
	FHitResult OutHit;
	FCollisionQueryParams TraceParams;
	FCollisionObjectQueryParams ObjectParams;
	ObjectParams.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	if (GetWorld()->LineTraceSingleByObjectType(OutHit, CurrentLocation, (CurrentLocation + GetActorForwardVector() * AvoidanceDistanceRange), ObjectParams, TraceParams))
	{
		//TSphericalFibonacci<float> PointGen(NumPoints);
		//UE_LOG(LogTemp, Warning, TEXT ("Collision Emminent With %s"), *(OutHit.GetActor()->GetName()))
		//FYi, I have no idea what aZimuth or inclination mean, I copied the code from https://stackoverflow.com/questions/9600801/evenly-distributing-n-points-on-a-sphere/44164075#44164075
		//I tried Using Unreal's TSphericalFibonacci for like 5 hours
			//Can't figure out how to rotate it to point into the forward vector tho, cus it was 3AM
			//Figured it out in the morning, but thought TSphericalFibonacci might be part of the problem, so I changed it :shrug:
			//in hindsight it would work anyway, but VS keeps throwing error message at me cus it doesn't know how module works
		int NumPoints = 1000;
		for (int i = 0; i < NumPoints; i++)
		{
			float t = (float)i / ((float)NumPoints - 1.0f);
			float inclination = FMath::Acos(1.0f - 2.0f * t);
			float azimuth = 2.0f * PI * UE_GOLDEN_RATIO * (float)i;

			float x = FMath::Sin(inclination) * FMath::Cos(azimuth);
			float y = FMath::Sin(inclination) * FMath::Sin(azimuth);
			float z = FMath::Cos(inclination);
			FVector PointPosition = FVector(-z, y, x);
			FVector RelativePosition = CurrentLocation + (-GetActorForwardVector()).Rotation().RotateVector(PointPosition) * AvoidanceDistanceRange;
			if (!GetWorld()->LineTraceSingleByObjectType(OutHit, CurrentLocation, RelativePosition, ObjectParams, TraceParams))
			{
				RotateToDirection(dt, RelativePosition, Strength);
				break;
			}
		}
		
	}
	
}


void ABoids::FireSequence(FVector CurrentLocation, FVector target)
{
	// Check if target exists first and if it has health so it doesnt keep shooting after its dead
	if (FollowTarget)
	{
		// Take the healthcomponent and check if its not dead
		UHealthComponent* TargetHealth = Cast<UHealthComponent>(FollowTarget->GetComponentByClass(UHealthComponent::StaticClass()));
		if (TargetHealth && TargetHealth->CurrentHealth > 0)
		{
			bFireable = false;
			UCharacterMovementComponent* Movement = GetCharacterMovement();
			Movement->StopMovementImmediately();
			Movement->MaxFlySpeed = 0;
			SetActorRotation(UKismetMathLibrary::FindLookAtRotation(CurrentLocation, target));
			UGameplayStatics::PlaySoundAtLocation(this, BeamSound, CurrentLocation);
			BeamParticle->SetBeamTargetPoint(0, target, 0);
			BeamParticle->SetVisibility(true);
			// Deal damage to the target
			TargetHealth->TakeDamage();
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, [&]()
				{
					GetCharacterMovement()->MaxFlySpeed = MaxFlySpeedTMP;
					BeamParticle->SetVisibility(false);
					//somehow this crashes it? //make except when follow target change reset the timer
					GetWorld()->GetTimerManager().SetTimer(TimerHandle2, [&]()
						{
							bFireable = true;
						}, UntilNextFire, false);
				}, FireDuration, false);
		}
	}
}

void ABoids::RotateToDirection(float dt, FVector target, float Strength)
{
	SetActorRotation(FMath::RInterpConstantTo(GetActorRotation() , UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), target),dt, Strength));
}

void ABoids::GetAllBoids()
{
	for (TActorIterator<ABoids> It(GetWorld()); It; ++It) {
		AllBoids.Add(*It);
		It->AllBoids.Add(this);
	}
	AllBoids.Remove(this);
}

void ABoids::Targetted()
{
	LockedOn.Broadcast(this); //A delegate Call
}

void ABoids::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ABoids, FollowTarget);
}





