// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviourTree.h"

// Sets default values for this component's properties
UBehaviourTree::UBehaviourTree()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBehaviourTree::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBehaviourTree::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBehaviourTree::SayHi()
{
	UE_LOG(LogTemp, Warning, TEXT("Hi"));
	GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Blue, FString::Printf(TEXT("Hello")));
}

