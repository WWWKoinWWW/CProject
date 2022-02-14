// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/02_Component/LockOnComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Camera/CameraComponent.h"
#include "00_Character/00_Player/PlayerCharacter.h"

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
	
}


// Called every frame
void ULockOnComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void ULockOnComponent::LockOn()
{
	UCameraComponent* camera;
	camera = GetOwner<APlayerCharacter>()->GetFollowCamera();
	FVector EndPoint = (camera->GetForwardVector() * 100.0f) + camera->GetComponentLocation();

	UKismetSystemLibrary::SphereTraceMulti(camera, camera->GetComponentLocation(), EndPoint);


	// 카메라 앞 방향 백터
	// n거리만큼 좌표
	// 카메라 앞 방향으로 n만큼의 거리까지 트레이스
	// 트레이스에 걸린 대상을 저장
	// 트레이스에 걸린 대상들 중 가장 가까운 대상을 타겟으로 저장
}