// Fill out your copyright notice in the Description page of Project Settings.


#include "RandomPatrolNode.h"


URandomPatrolNode::URandomPatrolNode()
{

}


URandomPatrolNode::URandomPatrolNode(UCharacterMovementComponent* NewMoveComp)
{
	MoveComp = NewMoveComp;
	Direction = FMath::VRand();
}

void URandomPatrolNode::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PatrolTime <= MaxPatrolTime)
	{
		PatrolTime += DeltaTime;
	}
}


NodeState URandomPatrolNode::RunState()
{
	// move the character if 1 sec has not passed 
	if (PatrolTime <= MaxPatrolTime)
	{
		State = NodeState::RUNNING;
		GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Red, TEXT("Moving..."));
	}

	// if 1 sec has passed, state is success
	if (PatrolTime >= MaxPatrolTime)
	{
		State = NodeState::SUCCESS;
	}

	return State;
}