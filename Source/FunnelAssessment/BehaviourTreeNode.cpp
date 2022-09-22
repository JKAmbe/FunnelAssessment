// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviourTreeNode.h"

// Sets default values for this component's properties
UBehaviourTreeNode::UBehaviourTreeNode()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

	ParentNode = nullptr;
}


UBehaviourTreeNode::UBehaviourTreeNode(TArray<UBehaviourTreeNode*> Children)
{
	for (UBehaviourTreeNode* i : Children)
	{
		AttachChild(i);
	}
}

// Called when the game starts
void UBehaviourTreeNode::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBehaviourTreeNode::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBehaviourTreeNode::AttachChild(UBehaviourTreeNode* Child)
{
	Child->ParentNode = this;
	ChildrenNode.Add(Child);
}

NodeState UBehaviourTreeNode::ReturnState()
{
	return NodeState::FAIL;
}


