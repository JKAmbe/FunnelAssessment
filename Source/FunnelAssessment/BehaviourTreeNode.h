// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BehaviourTreeNode.generated.h"

enum class NodeState : uint8{
	RUNNING,
	SUCCESS,
	FAIL
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUNNELASSESSMENT_API UBehaviourTreeNode : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBehaviourTreeNode();
	// override for when there are child nodes to be added
	UBehaviourTreeNode(TArray<UBehaviourTreeNode*> Children);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	NodeState State;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UBehaviourTreeNode* ParentNode;
	TArray<UBehaviourTreeNode*> ChildrenNode;

	void AttachChild(UBehaviourTreeNode* Child);
	virtual NodeState ReturnState();
};
