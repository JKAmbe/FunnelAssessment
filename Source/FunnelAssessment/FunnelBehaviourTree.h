// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BehaviourTree.h"
#include "RandomPatrolNode.h"
#include "FunnelBehaviourTree.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class FUNNELASSESSMENT_API UFunnelBehaviourTree : public UBehaviourTree
{
	GENERATED_BODY()
	
public:
	UTreeNode* SetupTree(UCharacterMovementComponent* NewMovementComponent);

	UCharacterMovementComponent* MoveComp;
	float MoveSpeed = 100.0f;
};
