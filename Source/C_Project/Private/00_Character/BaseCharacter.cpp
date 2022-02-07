// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/BaseCharacter.h"
#include "00_Character/99_Component/StatusComponent.h"


// Sets default values
ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
					  //�����ڿ����� ��� ����
	StatusComponent = CreateDefaultSubobject<UStatusComponent>(TEXT("StatusComponent"));
}

// Called when the game starts or when spawned
void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	//1. DamageAmount��ŭ ü���� ����.
	StatusComponent->AddHP((-1) * DamageAmount);
	//2. ���� ü���� �α׷� ����.
	UE_LOG(LogTemp, Log, TEXT("HP : %f"), StatusComponent->GetHP());

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

