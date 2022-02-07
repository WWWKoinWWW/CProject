// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/98_Animation/01_Notify/FootStepNotify.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"

void UFootStepNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp != nullptr)
	{
		FHitResult Hit;

		FVector StartLocation = MeshComp->GetSocketLocation(SocketName);
		FVector EndLocation = (StartLocation.DownVector * 50.0f) + StartLocation;

		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.bReturnPhysicalMaterial = true;
		CollisionQueryParams.AddIgnoredActor(MeshComp->GetOwner());

		//MeshComp->GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility, CollisionQueryParams);
		if (MeshComp->GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_Visibility, CollisionQueryParams))
		{
			if (Hit.PhysMaterial != nullptr)
			{
				switch (Hit.PhysMaterial->SurfaceType)
				{
				case EPhysicalSurface::SurfaceType_Default:
					SpawnSoundAndParticle(MeshComp->GetWorld(), DefaultSound, DefaultParticle, Hit.Location);
					break;
				case EPhysicalSurface::SurfaceType1:
					SpawnSoundAndParticle(MeshComp->GetWorld(), GroundSound, GroundParticle, Hit.Location);
					// Ground
					break;
				case EPhysicalSurface::SurfaceType2:
					SpawnSoundAndParticle(MeshComp->GetWorld(), GrassSound, GrassParticle, Hit.Location);
					// Grass
					break;
				case EPhysicalSurface::SurfaceType3:
					SpawnSoundAndParticle(MeshComp->GetWorld(), IceSound, IceParticle, Hit.Location);
					// Ice
					break;
				case EPhysicalSurface::SurfaceType4:
					SpawnSoundAndParticle(MeshComp->GetWorld(), SnowSound, SnowParticle, Hit.Location);
					// Snow
					break;
				case EPhysicalSurface::SurfaceType5:
					SpawnSoundAndParticle(MeshComp->GetWorld(), WaterSound, WaterParticle, Hit.Location);
					// Water
					break;
				}
			}
		}

		UKismetSystemLibrary::DrawDebugLine(MeshComp, StartLocation, EndLocation, FLinearColor::Blue, 0.3f, 1.0f);
	}
}

void UFootStepNotify::SpawnSoundAndParticle(UWorld* World, USoundBase* Sound, UNiagaraSystem* Particle, FVector SpawnLocation)
{
	if (Sound != nullptr)
	{
		UGameplayStatics::SpawnSoundAtLocation(World, Sound, SpawnLocation);
	}

	if (Particle != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(World, Particle, SpawnLocation);
	}
}
