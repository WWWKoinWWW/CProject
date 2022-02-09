// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "01_Item/00_Equipable/Equipment_Spawn.h"
#include "Weapon_Spawn.generated.h"

UCLASS()
class C_PROJECT_API AWeapon_Spawn : public AEquipment_Spawn
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon_Spawn();


protected:

	UPROPERTY()
		TArray<AActor*> HitActors;

	UPROPERTY(VisibleAnywhere)
		class UParticleSystemComponent* TrailComponent;

public:
	class UParticleSystemComponent* GetTrailComponent()
	{
		return TrailComponent;
	}
	//히트된 대상을 저장
	void AddUniqueHitActor(AActor* HitActor);
	//이미 히트한 대상인지 확인. 맞으면 참
	bool IsAlreadyHitActor(AActor* HitActor);
	//히트 액터 배열을 비움.
	void ClearHitActors();

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override; 
	UFUNCTION()
		void OnActorBeginOverlapEvent(AActor* OverlappedActor, AActor* OtherActor);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		class UNiagaraSystem* HitParticle;

	/*
	UPROPERTY(EditAnywhere)
		class UParticleSystem* HitParticle;
		*/
};
