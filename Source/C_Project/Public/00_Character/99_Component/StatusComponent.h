// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C_PROJECT_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

protected:

	UPROPERTY(EditAnywhere)
		float HP = 100;
	UPROPERTY(EditAnywhere)
		float MaxHP = 100;
	UPROPERTY(EditAnywhere)
		float SP = 100;
	UPROPERTY(EditAnywhere)
		float MaxSP = 100;


	// Called when the game starts
	virtual void BeginPlay() override;

public:

	float GetHP() { return HP; }
	float GetMaxHP() { return MaxHP; }
	float GetSP() { return SP; }
	float GetMaxSP() { return MaxSP; }

	UFUNCTION(BlueprintCallable)
		void AddSP(float Value);

	/**
	 * @brief Value값보다 SP가 많거나 같은지 확인합니다.
	 * @param Value 
	 * @return 많거나 같으면 참.
	 */
	bool CheckSP(float Value);

	UFUNCTION(BlueprintCallable)
		void AddHP(float Value);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
