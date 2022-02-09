// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "TrailNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API UTrailNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere)
		FName StartSocketName;
	UPROPERTY(EditAnywhere)
		FName EndSocketName;
	UPROPERTY(EditAnywhere)
		TEnumAsByte<ETrailWidthMode> TrailWidthMode;
	UPROPERTY(EditAnywhere)
		float Width;
	
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

};
