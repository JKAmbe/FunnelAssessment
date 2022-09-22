// Fill out your copyright notice in the Description page of Project Settings.


#include "BT_Funnel.h"
#include "BTNode_FunnelMoveToPoint.h"

UBT_Funnel::UBT_Funnel()
{
	SetupTree();

}

UBehaviourTreeNode* UBT_Funnel::SetupTree()
{
	UE_LOG(LogTemp, Warning, TEXT("Running setup"));
	// create a new movetopoint node and assign it as root node
	UBTNode_FunnelMoveToPoint* Move1 = CreateDefaultSubobject<UBTNode_FunnelMoveToPoint>(TEXT("Move1"));
	RootNode = Move1;
	return RootNode;
}

void UBT_Funnel::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	
}
