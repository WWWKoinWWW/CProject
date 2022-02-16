// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/02_Component/LockOnComponent.h"

#include "00_Character/00_Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
ULockOnComponent::ULockOnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULockOnComponent::BeginPlay()
{
	Super::BeginPlay();

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
			LockOnableActors.AddUnique(Hits[i].GetActor());
		}

		//Ÿ���� ����ִ� ��� Ÿ���� ������ �ݴϴ�.
		if(LockOnTarget == nullptr)
		{
			SortLockOnableActors();
			if (LockOnableActors.IsValidIndex(0)) {
				LockOnTarget = LockOnableActors[0];
				OnTargetLockOn.Broadcast(LockOnTarget);
			}
		}
	}
}

void ULockOnComponent::SortLockOnableActors()
{
	if(Player == nullptr)
	{
		return;
	}

	LockOnableActors.Sort([this](const AActor& fst, const AActor& sec)
	{
			return Player->GetDistanceTo(&fst) > Player->GetDistanceTo(&sec);
	});



}

void ULockOnComponent::CameraLookAtTarget()
{

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
