// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedHP, class UStatusComponent*, statComp);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnChangedSP, class UStatusComponent*, statComp);

/*
 BlueprintType - 에디터내부에서 사용 가능한 Enum
 항상 Enum 이름 앞에 E가 붙어야 함.
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

	//델리게이트에 저장할 함수는 반드시 UFUNCTION 매크로 붙일 것.
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
	 * @param DamageAmount 피해량
	 * @param DamageEvent 피해에 대한 필요한 정보를 저장하는 구조체
	 * @param EventInstigator 이 대상에게 피해를 준 컨트롤러
	 * @param DamageCauser 어느 물체에 의해서 피해를 입었는가?
	 * @return 최종피해량
	 */
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
};
