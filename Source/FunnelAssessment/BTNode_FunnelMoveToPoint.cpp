// Fill out your copyright notice in the Description page of Project Settings.


#include "BTNode_FunnelMoveToPoint.h"

UBTNode_FunnelMoveToPoint::UBTNode_FunnelMoveToPoint()
{

}

UBTNode_FunnelMoveToPoint::UBTNode_FunnelMoveToPoint(float MoveSpeed, FVector Direction)
{
	number += MoveSpeed;
	if (number <= Direction.X)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), number);
	}
}

NodeState UBTNode_FunnelMoveToPoint::ReturnState()
{
	return NodeState::FAIL;
}