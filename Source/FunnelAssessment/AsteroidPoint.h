// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AsteroidPoint.generated.h"

UCLASS()
class FUNNELASSESSMENT_API AAsteroidPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAsteroidPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	USceneComponent* LocationComponent;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
};
