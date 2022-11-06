// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Net/UnrealNetwork.h"
#include "NetworkingTest.generated.h"

UCLASS()
class FUNNELASSESSMENT_API ANetworkingTest : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANetworkingTest();

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite)
		FString FollowTarget;
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSprintStart();
	void SprintStart();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
