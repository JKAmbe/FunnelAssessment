// Fill out your copyright notice in the Description page of Project Settings.


#include "FunnelBehaviourTree.h"

UTreeNode* UFunnelBehaviourTree::SetupTree(UCharacterMovementComponent* NewMovementComponent)
{

	UE_LOG(LogTemp, Warning, TEXT("Hi"));
	if (NewMovementComponent != nullptr)
	{
		MoveComp = NewMovementComponent;
	}
	URandomPatrolNode* Random1 = NewObject<URandomPatrolNode>();
	RootNode = Random1;
	return RootNode;
}