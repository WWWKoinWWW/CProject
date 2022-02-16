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

	//Ÿ���� ���������� ȣ��Ǵ� �̹�Ʈ�Դϴ�.
	UPROPERTY(BlueprintAssignable)
		FOnTargetLockOn OnTargetLockOn;
	//Ÿ�ٿ��� ���� ������ ��� �̵���Ű�� ��������Ʈ �����Դϴ�.
	UPROPERTY(BlueprintAssignable)
		FOnLockOnWigetPosUpdate OnLockOnWigetPosUpdate;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY()
		class APlayerCharacter* Player;
	UPROPERTY()
		class UCameraComponent* CameraComponent;
	
	UPROPERTY() // �ǽð� ����
		TArray<AActor*> LockOnableActors_Sort;
	UPROPERTY() // ���� ����
		TArray<AActor*> LockOnableActors;

	UPROPERTY(EditAnywhere)
		float LockOnDistance;
	UPROPERTY(EditAnywhere)
		float Radius;


	UPROPERTY()
		AActor* LockOnTarget;

	/**
	 * @brief ī�޶�� ���� ���� ����� ������ Ʈ���̽��� �׸��ϴ�.
	 */
	void CreateCameraTrace();
	/**
	 * @brief ����� �÷��̾�� �ʹ� �־����� ���� ��󿡼� �����մϴ�.
	 */
	UFUNCTION(BlueprintCallable)
	void SortLockOnableActors();
	/**
	 * @brief ī�޶� Ÿ���� �ٶ󺸰� �մϴ�.
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
