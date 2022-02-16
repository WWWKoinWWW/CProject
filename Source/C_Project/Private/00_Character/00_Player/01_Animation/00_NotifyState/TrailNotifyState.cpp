// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/01_Animation/00_NotifyState/TrailNotifyState.h"
#include "00_Character/00_Player/PlayerCharacter.h"
#include "Components/ChildActorComponent.h"
#include "01_Item/00_Equipable/Weapon_Spawn.h"
#include "particles/ParticleSystemComponent.h"

//������ ���� ���� �� -> SocketName, Width, ETrailWidthMode
//���� TrailComponent�� BeginTrails ȣ��
void UTrailNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);
	if(MeshComp!=nullptr)
	{
		auto Player = MeshComp->GetOwner<APlayerCharacter>();
		if (Player != nullptr) {
			auto Weapon = Player->GetWeapon();
			if (Weapon != nullptr)
			{
				Weapon->GetTrailComponent()->BeginTrails(StartSocketName,
					EndSocketName, TrailWidthMode, Width);

			}
		}
	}
}

//���� TrailComponent�� EndTrails ȣ��
void UTrailNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (MeshComp != nullptr)
	{
		auto Player = MeshComp->GetOwner<APlayerCharacter>();
		if (Player != nullptr) {
			auto Weapon = Player->GetWeapon();
			if (Weapon != nullptr)
			{
				Weapon->GetTrailComponent()->EndTrails();

			}
		}
	}
}
