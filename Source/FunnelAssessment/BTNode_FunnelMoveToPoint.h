// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviourTreeNode.h"
#include "BTNode_FunnelMoveToPoint.generated.h"

/**
 * 
 */
UCLASS()
class FUNNELASSESSMENT_API UBTNode_FunnelMoveToPoint : public UBehaviourTreeNode
{
	GENERATED_BODY()
public:
	UBTNode_FunnelMoveToPoint();
	UBTNode_FunnelMoveToPoint(float MoveSpeed, FVector Direction);

	NodeState ReturnState() override;

	float number = 0.0f;
};
