// Fill out your copyright notice in the Description page of Project Settings.

#include "Net/UnrealNetwork.h"
#include "NetworkingTest.h"

// Sets default values
ANetworkingTest::ANetworkingTest()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	FollowTarget = TEXT("sussy");
}

//void ANetworkingTest::ServerChangeVar_Implementation(AActor* NewValue)
//{
//	FollowTarget = NewValue;
//}

void ANetworkingTest::SprintStart()
{
	FollowTarget = TEXT("Yest");
	ServerSprintStart();
}


// Called when the game starts or when spawned
void ANetworkingTest::BeginPlay()
{
	Super::BeginPlay();
	bReplicates = true;
}

void ANetworkingTest::ServerSprintStart_Implementation()
{
	FollowTarget = TEXT("Yest");
	//GetCharacterMovement()->MaxWalkSpeed = SprintMovementSpeed;
}
bool ANetworkingTest::ServerSprintStart_Validate()
{
	return true;
}

// Called every frame
void ANetworkingTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SprintStart();
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s %i"), *FollowTarget, GetLocalRole()));
	//if (GetLocalRole() == ROLE_AutonomousProxy)
		//ServerChangeVar(FollowTarget);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%s"), *GetDebugName(FollowTarget)));
}

void ANetworkingTest::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ANetworkingTest, FollowTarget);
}


