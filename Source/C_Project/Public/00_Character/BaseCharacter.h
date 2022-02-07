// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedHP, class UStatusComponent*, statComp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedSP, class UStatusComponent*, statComp);

/*
 BlueprintType - �����ͳ��ο��� ��� ������ Enum
 �׻� Enum �̸� �տ� E�� �پ�� ��.
 */
UENUM(BlueprintType)
enum class EActionState : uint8
{
	NORMAL,
	RUN,
	ROLL,
	ATTACK,
	JUMP
};

UCLASS()
class C_PROJECT_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseCharacter();

	UPROPERTY(BlueprintAssignable)
		FOnChangedHP OnChangedHP;
	UPROPERTY(BlueprintAssignable)
		FOnChangedSP OnChangedSP;

protected:

	//��������Ʈ�� ������ �Լ��� �ݵ�� UFUNCTION ��ũ�� ���� ��.
	UFUNCTION()
		virtual void OnChangedHPEvent(class UStatusComponent* statComp){ }
	UFUNCTION()
		virtual void OnChangedSPEvent(class UStatusComponent* statComp) { }

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UStatusComponent* StatusComponent;

	UPROPERTY(BlueprintReadOnly)
		EActionState ActionState;

	virtual void SetActionState(EActionState newState){ }
public:
	EActionState GetActionState() { return ActionState; }


	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UStatusComponent* GetStatusComponent() { return StatusComponent; }

	/**
	 * @brief 
	 * @param DamageAmount ���ط�
	 * @param DamageEvent ���ؿ� ���� �ʿ��� ������ �����ϴ� ����ü
	 * @param EventInstigator �� ��󿡰� ���ظ� �� ��Ʈ�ѷ�
	 * @param DamageCauser ��� ��ü�� ���ؼ� ���ظ� �Ծ��°�?
	 * @return �������ط�
	 */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
