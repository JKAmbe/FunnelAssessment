// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviourTreeNode.h"
#include "BehaviourTreeSelector.generated.h"

/**
 * 
 */
UCLASS()
class FUNNELASSESSMENT_API UBehaviourTreeSelector : public UBehaviourTreeNode
{
	GENERATED_BODY()
	
public:
	NodeState ReturnState() override;
};
