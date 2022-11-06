// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Boids.h"
#include "Marker.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTargetDelegate);
UCLASS()
class FUNNELASSESSMENT_API UMarker : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void Reset();
	UPROPERTY(BlueprintAssignable, BlueprintCallable)
		FTargetDelegate OnMarked;
};
