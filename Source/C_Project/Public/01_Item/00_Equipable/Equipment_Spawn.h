// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Equipment_Spawn.generated.h"

UCLASS()
class C_PROJECT_API AEquipment_Spawn : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEquipment_Spawn();

protected:

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* EquipmentMeshComponent;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UStaticMeshComponent* GetEquipmentMeshComponent() { return EquipmentMeshComponent; }

	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
