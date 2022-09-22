// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BT_Funnel.h"
#include "Funnel.generated.h"

UCLASS()
class FUNNELASSESSMENT_API AFunnel : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFunnel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// variable for behavior tree
	UPROPERTY(EditAnywhere)
		UBT_Funnel* BehaviourTree;

};
