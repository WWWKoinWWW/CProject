// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/02_Component/LockOnComponent.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
ULockOnComponent::ULockOnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void ULockOnComponent::OnEndLockOnEvent()
{
	SetComponentTickEnabled(false);
	ClearLockOnActors();
}

// Called when the game starts
void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();

	SetComponentTickEnabled(false);

	//OnEndLockOn.Add(&ULockOnComponent::OnEndLockOnEvent);@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	// ...
	Player = GetOwner<APlayerCharacter>();
	if(Player!=nullptr)
	{
		CameraComponent = Player->GetFollowCamera();
	}
	
}


void ULockOnComponent::CreateCameraTrace()
{
	TArray<FHitResult> Hits;
	FVector EndPoint = (CameraComponent->GetForwardVector() * LockOnDistance) + CameraComponent->GetComponentLocation();


	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectType;
	ObjectType.Emplace(UEngineTypes::ConvertToObjectType(ECC_GameTraceChannel1));

	if (UKismetSystemLibrary::SphereTraceMultiForObjects(this,
		CameraComponent->GetComponentLocation(),
		EndPoint,
		Radius,
		ObjectType,
		false,
		TArray<AActor*>(),
		EDrawDebugTrace::ForOneFrame, Hits, true))
	{

		//�ɸ� ������ �� ������Ʈ�� ����.
		for (auto i = 0; i < Hits.Num(); i++)
		{
			LockOnableActors_Sort.AddUnique(Hits[i].GetActor());
			LockOnableActors.AddUnique(Hits[i].GetActor());
		}

		//Ÿ���� ����ִ� ��� Ÿ���� ������ �ݴϴ�.
		if(LockOnTarget == nullptr)
		{
			// �ɸ� ���� ����
			SortLockOnableActors();
			
			// ���� ����� ����� Ÿ������ ��
			LockOnTarget = LockOnableActors_Sort[0];
			OnTargetLockOn.Broadcast(LockOnTarget);
		}
	}
	else
	{
		if (LockOnableActors.Num() == 0)
		{
			Player->LockOn();
		}
	}
}

void ULockOnComponent::SortLockOnableActors()
{
	if(Player == nullptr)
	{
		return;
	}

	// �Ÿ� �������� ����, ���ٽ�
	LockOnableActors_Sort.Sort([this](const AActor& fst, const AActor& sec)
		{
			return Player->GetDistanceTo(&fst) > Player->GetDistanceTo(&sec);
		});

	// �����Ÿ� �̻� �־��� ����� ����
	for (auto i = 0; i < LockOnableActors_Sort.Num(); i++)
	{
		auto Target = LockOnableActors_Sort[i];
		if (Player->GetDistanceTo(LockOnableActors_Sort[i]) >= 1500.0f)
		{
			LockOnableActors_Sort.RemoveAt(i);
			LockOnableActors.Remove(Target);

			if (Target == LockOnTarget)
			{
				if (LockOnableActors.Num() > 0)
				{
					SetNextLockOnTarket();
				}
			}
		}
	}
}

void ULockOnComponent::CameraLookAtTarget()
{
	if (LockOnTarget != nullptr)
	{
		USpringArmComponent* CameraBoom = Player->GetCameraBoom();
		/*
		1. ī�޶� ���� Ÿ���� �ٶ� ����(Rotation)
		2. ���� ������ �÷��̾� ��Ʈ�ѷ��� �����̼��� ����
		*/
		FVector Start = LockOnTarget->GetActorLocation();
		FVector End = CameraBoom->GetComponentLocation();
		FRotator Rot = (Start - End).Rotation();

		Player->GetController()->SetControlRotation(Rot);
	}
}

void ULockOnComponent::SetNextLockOnTarket()
{
	if (LockOnableActors.Num() > 1)
	{
		AActor* NextTarget = LockOnableActors[0];
		LockOnableActors.RemoveAt(0);
		LockOnableActors.Push(NextTarget);

		if (LockOnTarget == NextTarget)
		{
			SetNextLockOnTarket();
		}
		else
		{
			LockOnTarget = NextTarget;
			OnTargetLockOn.Broadcast(LockOnTarget);
		}
	}
}

void ULockOnComponent::SetPreLockOnTarget()
{
	if (LockOnableActors.Num() > 1)
	{
		AActor* PreTarget = LockOnableActors.Pop();
		LockOnableActors.Push(PreTarget);

		if (LockOnTarget == PreTarget)
		{
			SetNextLockOnTarket();
		}
		else
		{
			LockOnTarget = PreTarget;
			OnTargetLockOn.Broadcast(LockOnTarget);
		}
	}
}

void ULockOnComponent::ClearLockOnActors()
{
	LockOnableActors.Empty();
	LockOnableActors_Sort.Empty();
	LockOnTarget = nullptr;
}



// Called every frame
void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...

	//1.ī�޶� Ʈ���̽��� ������ ������.
	CreateCameraTrace();
	//2.������ ������.
	SortLockOnableActors();
	//3.ī�޶�� �ٶ�
	CameraLookAtTarget();
	//4.���� ������ ��ġ�� ������Ʈ ��.
	OnLockOnWigetPosUpdate.Broadcast(LockOnTarget);
}

void ULockOnComponent::LockOn()
{

}
