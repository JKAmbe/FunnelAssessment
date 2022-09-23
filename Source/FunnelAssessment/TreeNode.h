// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TreeNode.generated.h"

UENUM()
enum class NodeState : uint8
{
	RUNNING,
	SUCCESS,
	FAILURE
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUNNELASSESSMENT_API UTreeNode : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTreeNode();
	UTreeNode(TArray<UTreeNode*> NewChildren);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	NodeState State;
	TArray<UTreeNode*> Children;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual NodeState RunState();

	void Attach(UTreeNode* Node);

	UTreeNode* ParentNode;
};
