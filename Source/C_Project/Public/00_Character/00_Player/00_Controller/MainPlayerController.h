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

	//��Ʈ�ѷ��� �ش� ���� ���ǵǴ� ������ ȣ���.
	virtual void OnPossess(APawn* aPawn) override;

	/// <summary>
	/// Ư�� ����� ���µǾ����� ȣ��Ǵ� �Լ��Դϴ�.
	/// </summary>
	UFUNCTION()
		void OnTargetLockOnEvent(AActor* Target);
	/// <summary>
	/// Ÿ���� ��ġ�� ������ ��ġ�� ������Ʈ �մϴ�.
	/// </summary>
	UFUNCTION()
		void OnLockOnWigetPosUpdateEvent(AActor* Target);
public:
	UMainWidget* GetMainWidget() { return MainWidget; }
};
