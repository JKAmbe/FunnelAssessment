// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviourTree.h"
#include "BTNode_FunnelMoveToPoint.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BT_Funnel.generated.h"

/**
 * 
 */
UCLASS(meta=(BlueprintSpawnableComponent))
class FUNNELASSESSMENT_API UBT_Funnel : public UBehaviourTree
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties

protected:
	UBT_Funnel();
	// Called when the game starts
	//virtual void BeginPlay() override;
	UBehaviourTreeNode* SetupTree() override;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere)
		float MoveSpeed = 0.0f;
	UPROPERTY(EditAnywhere)
		FVector Direction = FVector(0, 0, 0);
	
	UCharacterMovementComponent* MoveComp;
};
