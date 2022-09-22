// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviourTreeSequence.h"

// if all child nodes succeed, return success, if not return fail
NodeState UBehaviourTreeSequence::ReturnState()
{
	bool ChildRunning = false;
	for (UBehaviourTreeNode* i : ChildrenNode)
	{
		switch (i->ReturnState())
		{
		case NodeState::FAIL:
			State = NodeState::FAIL;
			return State;
		case NodeState::SUCCESS:
			// nothing
		case NodeState::RUNNING:
			ChildRunning = true;
		}
	}
	// if any child is running, this state is running, if not and node state does not return fail, its a success
	State = ChildRunning ? NodeState::RUNNING : NodeState::SUCCESS;
	return State;
}