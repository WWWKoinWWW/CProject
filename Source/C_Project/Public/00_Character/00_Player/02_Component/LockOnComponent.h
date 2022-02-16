// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LockOnComponent.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTargetLockOn, AActor*, Target);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLockOnWigetPosUpdate, AActor*, Target);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class C_PROJECT_API ULockOnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULockOnComponent();

	//타겟을 락온했을때 호출되는 이밴트입니다.
	UPROPERTY(BlueprintAssignable)
		FOnTargetLockOn OnTargetLockOn;
	//타겟에게 락온 위젯을 계속 이동시키는 델리게이트 변수입니다.
	UPROPERTY(BlueprintAssignable)
		FOnLockOnWigetPosUpdate OnLockOnWigetPosUpdate;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
		class APlayerCharacter* Player;
	UPROPERTY()
		class UCameraComponent* CameraComponent;
	
	UPROPERTY() // 실시간 정렬
		TArray<AActor*> LockOnableActors_Sort;
	UPROPERTY() // 정렬 안함
		TArray<AActor*> LockOnableActors;

	UPROPERTY(EditAnywhere)
		float LockOnDistance;
	UPROPERTY(EditAnywhere)
		float Radius;


	UPROPERTY()
		AActor* LockOnTarget;

	/**
	 * @brief 카메라로 부터 락온 대상을 가져올 트레이스를 그립니다.
	 */
	void CreateCameraTrace();
	/**
	 * @brief 대상이 플레이어와 너무 멀어지면 락온 대상에서 제외합니다.
	 */
	UFUNCTION(BlueprintCallable)
	void SortLockOnableActors();
	/**
	 * @brief 카메라가 타겟을 바라보게 합니다.
	 */
	void CameraLookAtTarget();

public:	

	void SetNextLockOnTarket();
	void SetPreLockOnTarget();
	void ClearLockOnActors();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void LockOn();
};
