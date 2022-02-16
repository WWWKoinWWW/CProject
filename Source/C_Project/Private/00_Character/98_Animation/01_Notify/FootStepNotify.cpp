// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/98_Animation/01_Notify/FootStepNotify.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

void UFootStepNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if(MeshComp != nullptr)
	{
		FHitResult Hit;

		FVector StartLocation = MeshComp->GetSocketLocation(SocketName);
		//StartLocation으로 부터 아래로 N만큼의 좌표
		FVector EndLocation = (StartLocation.DownVector * 50.f) + StartLocation;

		FCollisionQueryParams CollisionQueryParams;
		//물체 표면 타입을 읽어옵니다.
		CollisionQueryParams.bReturnPhysicalMaterial = true;
		CollisionQueryParams.AddIgnoredActor(MeshComp->GetOwner());


		if(MeshComp->GetWorld()->LineTraceSingleByChannel(Hit,StartLocation,EndLocation,ECC_Visibility, CollisionQueryParams))
		{

			if (Hit.PhysMaterial != nullptr)
			{
				switch (Hit.PhysMaterial->SurfaceType)
				{
				case EPhysicalSurface::SurfaceType_Default:
					SpawnSoundAndParticle(MeshComp->GetWorld(), DefaultSound, DefaultParticle, Hit.Location);
					break;
					//Ground
				case EPhysicalSurface::SurfaceType1:
					SpawnSoundAndParticle(MeshComp->GetWorld(), GroundSound, GroundParticle, Hit.Location);
					break;
					//Grass
				case EPhysicalSurface::SurfaceType2:
					SpawnSoundAndParticle(MeshComp->GetWorld(), GrassSound, GrassParticle, Hit.Location);
					break;
					//Ice
				case EPhysicalSurface::SurfaceType3:
					SpawnSoundAndParticle(MeshComp->GetWorld(), IceSound, IceParticle, Hit.Location);
					break;
					//Snow
				case EPhysicalSurface::SurfaceType4:
					SpawnSoundAndParticle(MeshComp->GetWorld(), SnowSound, SnowParticle, Hit.Location);
					break;
					//Water
				case EPhysicalSurface::SurfaceType5:
					SpawnSoundAndParticle(MeshComp->GetWorld(), WaterSound, WaterParticle, Hit.Location);
					break;
				case EPhysicalSurface::SurfaceType6:
					SpawnSoundAndParticle(MeshComp->GetWorld(), WoodSound, WoodParticle, Hit.Location);
					break;
				case EPhysicalSurface::SurfaceType7:
					SpawnSoundAndParticle(MeshComp->GetWorld(), SandSound, SandParticle, Hit.Location);
					break;
				case EPhysicalSurface::SurfaceType8:
					SpawnSoundAndParticle(MeshComp->GetWorld(), DirtSound, DirtParticle, Hit.Location);
					break;
				}
			}
			
		}

		UKismetSystemLibrary::DrawDebugLine(MeshComp, StartLocation, EndLocation, FLinearColor::Blue, 0.3f, 1.f);
	}
}

void UFootStepNotify::SpawnSoundAndParticle(UWorld* World, USoundBase* Sound, UNiagaraSystem* Particle, FVector SpawnLocation)
{
	if(Sound!=nullptr)
	{
		UGameplayStatics::SpawnSoundAtLocation(World, Sound, SpawnLocation);
	}

	if(Particle!=nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, Particle, SpawnLocation);
	}
}
