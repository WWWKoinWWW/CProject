// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CheckInputNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class UCheckInputNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
protected:

	UCheckInputNotifyState();

	UPROPERTY()
		class APlayerCharacter* Player;

	UPROPERTY()
		bool bContinue = false;
	/*
	 *	FString
	 *	FName	-	검색용(대소문자 구분 안 함)
	 *	FText	-	UI전용
	 */
	UPROPERTY(EditAnywhere)
		FName NextSection;

	virtual void BranchingPointNotifyBegin(FBranchingPointNotifyPayload& BranchingPointPayload) override;
	virtual void BranchingPointNotifyTick(FBranchingPointNotifyPayload& BranchingPointPayload, float FrameDeltaTime) override;
	virtual void BranchingPointNotifyEnd(FBranchingPointNotifyPayload& BranchingPointPayload) override;
};
