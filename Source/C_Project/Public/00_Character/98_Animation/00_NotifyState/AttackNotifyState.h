// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "Engine/EngineTypes.h"
#include "AttackNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API UAttackNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
protected:

	UPROPERTY()
		class ABaseCharacter* Owner;

	UPROPERTY(EditAnywhere)
		FName StartSocket;
	UPROPERTY(EditAnywhere)
		FName EndSocket;
	UPROPERTY(EditAnywhere)
		float Radius;
	UPROPERTY(EditAnywhere)
		TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;

	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation);

};
