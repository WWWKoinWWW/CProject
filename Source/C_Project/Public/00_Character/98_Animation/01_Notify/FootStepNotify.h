// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "FootStepNotify.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API UFootStepNotify : public UAnimNotify
{
	GENERATED_BODY()
	
protected:

	UPROPERTY(EditAnywhere)
		class USoundBase* DefaultSound;
	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* DefaultParticle;

	UPROPERTY(EditAnywhere)
		class USoundBase* GroundSound;
	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* GroundParticle;

	UPROPERTY(EditAnywhere)
		class USoundBase* GrassSound;
	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* GrassParticle;

	UPROPERTY(EditAnywhere)
		class USoundBase* IceSound;
	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* IceParticle;

	UPROPERTY(EditAnywhere)
		class USoundBase* SnowSound;
	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* SnowParticle;

	UPROPERTY(EditAnywhere)
		class USoundBase* WaterSound;
	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* WaterParticle;

	UPROPERTY(EditAnywhere)
		FName SocketName;

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	void SpawnSoundAndParticle(class UWorld* World, class USoundBase* Sound, class UNiagaraSystem* Particle, FVector SpawnLocation);
};
