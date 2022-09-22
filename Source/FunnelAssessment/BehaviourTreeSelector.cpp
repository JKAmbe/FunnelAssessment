// Fill out your copyright notice in the Description page of Project Settings.


#include "BehaviourTreeSelector.h"


// return success if one of the child is a success, else return fail
NodeState UBehaviourTreeSelector::ReturnState()
{
	bool ChildRunning = false;
	for (UBehaviourTreeNode* i : ChildrenNode)
	{
		switch (i->ReturnState())
		{
		case NodeState::FAIL:
			//nothing
		case NodeState::SUCCESS:
			State = NodeState::SUCCESS;
			return State;
		case NodeState::RUNNING:
			State = NodeState::RUNNING;
			return State;
		}
	}
	// if state is not running or sucess, it failed
	State = NodeState::FAIL;
	return State;
}