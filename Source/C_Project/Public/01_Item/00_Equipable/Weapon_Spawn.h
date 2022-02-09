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
	//��Ʈ�� ����� ����
	void AddUniqueHitActor(AActor* HitActor);
	//�̹� ��Ʈ�� ������� Ȯ��. ������ ��
	bool IsAlreadyHitActor(AActor* HitActor);
	//��Ʈ ���� �迭�� ���.
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
