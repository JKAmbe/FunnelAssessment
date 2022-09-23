// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TreeNode.h"
#include "GameFramework/Character.h"
#include "RandomPatrolNode.generated.h"

/**
 * 
 */

// Every second, move to a random direction
UCLASS()
class FUNNELASSESSMENT_API URandomPatrolNode : public UTreeNode
{
	GENERATED_BODY()
	
public:
	URandomPatrolNode();
	URandomPatrolNode(UCharacterMovementComponent* NewMoveComp);

public:
	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	NodeState RunState();

	float MaxPatrolTime = 1.0f;
	float PatrolTime = 0.0f;
	UCharacterMovementComponent* MoveComp;
	FVector Direction;
};
