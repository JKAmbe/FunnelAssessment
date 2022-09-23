// Fill out your copyright notice in the Description page of Project Settings.


#include "Funnel.h"

// Sets default values
AFunnel::AFunnel()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FunnelBehaviourTree = FindComponentByClass<UBehaviourTree>();
}

// Called when the game starts or when spawned
void AFunnel::BeginPlay()
{
	Super::BeginPlay();
	FunnelBehaviourTree = FindComponentByClass<UBehaviourTree>();
	if (FunnelBehaviourTree != nullptr)
	{
		FunnelBehaviourTree->SayHi();
	}
	
}

// Called every frame
void AFunnel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFunnel::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
