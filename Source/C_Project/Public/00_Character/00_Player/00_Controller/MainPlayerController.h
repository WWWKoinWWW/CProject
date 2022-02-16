// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class C_PROJECT_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UMainWidget> MainWidgetObject;
	UPROPERTY()
		UMainWidget* MainWidget;


	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> LockOnWidgetObject;
	UPROPERTY()
		class UUserWidget* LockOnWidget;

	//컨트롤러가 해당 폰에 빙의되는 시점에 호출됨.
	virtual void OnPossess(APawn* aPawn) override;

	/// <summary>
	/// 특정 대상이 락온되었을때 호출되는 함수입니다.
	/// </summary>
	UFUNCTION()
		void OnTargetLockOnEvent(AActor* Target);
	/// <summary>
	/// 타겟의 위치로 위젯의 위치를 업데이트 합니다.
	/// </summary>
	UFUNCTION()
		void OnLockOnWigetPosUpdateEvent(AActor* Target);
public:
	UMainWidget* GetMainWidget() { return MainWidget; }
};
