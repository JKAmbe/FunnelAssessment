// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeNode.h"

// Sets default values for this component's properties
UTreeNode::UTreeNode()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

UTreeNode::UTreeNode(TArray<UTreeNode*> NewChildren)
{
	for (UTreeNode* i : NewChildren)
	{
		Attach(i);
	}
}

// Called when the game starts
void UTreeNode::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}



// Called every frame
void UTreeNode::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

NodeState UTreeNode::RunState()
{
	return NodeState::FAILURE;
}

void UTreeNode::Attach(UTreeNode* Node)
{
	Node->ParentNode = this;
	Children.Add(Node);
}