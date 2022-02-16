// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "00_Character/BaseCharacter.h"
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API AMonster : public ABaseCharacter
{
	GENERATED_BODY()
public:

	AMonster();

protected:

	virtual void PostInitializeComponents() override;

	virtual void OnChangedHPEvent(class UStatusComponent* statComp) override;

	virtual void BeginPlay() override;

};
