// Fill out your copyright notice in the Description page of Project Settings.


#include "00_Character/00_Player/PlayerCharacter.h"

#include "00_Character/99_Component/StatusComponent.h"
#include "01_Item/00_Equipable/Weapon_Spawn.h"
#include "98_Widget/00_Player/MainWidget.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/ChildActorComponent.h"
#include "00_Character/00_Player/02_Component/LockOnComponent.h"

APlayerCharacter::APlayerCharacter() {
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->MaxWalkSpeed = 300;
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GloveMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GloveMeshComponent"));
	GloveMeshComponent->SetupAttachment(GetMesh());
	GloveMeshComponent->SetMasterPoseComponent(GetMesh());

	BeltMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BeltMeshComponent"));
	BeltMeshComponent->SetupAttachment(GetMesh());
	BeltMeshComponent->SetMasterPoseComponent(GetMesh());

	FaceMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FaceMeshComponent"));
	FaceMeshComponent->SetupAttachment(GetMesh());
	FaceMeshComponent->SetMasterPoseComponent(GetMesh());

	HairMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HairMeshComponent"));
	HairMeshComponent->SetupAttachment(GetMesh());
	HairMeshComponent->SetMasterPoseComponent(GetMesh());

	HelmetMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("HelmetMeshComponent"));
	HelmetMeshComponent->SetupAttachment(GetMesh());
	HelmetMeshComponent->SetMasterPoseComponent(GetMesh());

	ShoesMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShoesMeshComponent"));
	ShoesMeshComponent->SetupAttachment(GetMesh());
	ShoesMeshComponent->SetMasterPoseComponent(GetMesh());

	ShoulderMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("ShoulderMeshComponent"));
	ShoulderMeshComponent->SetupAttachment(GetMesh());
	ShoulderMeshComponent->SetMasterPoseComponent(GetMesh());


	WeaponActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("WeaponActorComponent"));
	WeaponActorComponent->SetupAttachment(GetMesh(), "hand_rSocket");

	ShieldActorComponent = CreateDefaultSubobject<UChildActorComponent>(TEXT("ShieldActorComponent"));
	ShieldActorComponent->SetupAttachment(GetMesh(), "hand_lSocket");

	LockOnComponent = CreateDefaultSubobject<ULockOnComponent>(TEXT("LockOnComponent"));

}


AWeapon_Spawn* APlayerCharacter::GetWeapon()
{
	if(WeaponActorComponent == nullptr || WeaponActorComponent->GetChildActor()== nullptr)
	{
		return nullptr;
	}

	return Cast<AWeapon_Spawn>(WeaponActorComponent->GetChildActor());
}

void APlayerCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}

}

void APlayerCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}

}

void APlayerCharacter::TurnAtRate(float Rate)
{	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());

}

void APlayerCharacter::LookUpAtRate(float Rate)
{	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());

}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &APlayerCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &APlayerCharacter::StopRun);

	PlayerInputComponent->BindAction("Roll", IE_Pressed, this, &APlayerCharacter::Roll);

	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &APlayerCharacter::Attack);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &APlayerCharacter::StopAttack);

	PlayerInputComponent->BindAction("LockOn", IE_Pressed, this, &APlayerCharacter::LockOn);



	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpAtRate);

	

}

void APlayerCharacter::LockOn()
{
	LockOnComponent->LockOn();

}



void APlayerCharacter::StopRun()
{
	SetActionState(EActionState::NORMAL);
}

void APlayerCharacter::Roll()
{
	if(GetCharacterMovement()->IsFalling())
	{
		return;
	}


	if (ActionState != EActionState::ROLL && StatusComponent->CheckSP(30.f)) {
		StatusComponent->AddSP(-30.f);
		SetActionState(EActionState::ROLL);
	}
}

void APlayerCharacter::Attack()
{
	bPressAttack = true;

	if (GetCharacterMovement()->IsFalling())
	{
		return;
	}

	if (ActionState != EActionState::ATTACK && StatusComponent->CheckSP(25.f)) {
		StatusComponent->AddSP(-25.f);
		SetActionState(EActionState::ATTACK);
	}
}

void APlayerCharacter::StopAttack()
{
	bPressAttack = false;
}

void APlayerCharacter::Run()
{
	SetActionState(EActionState::RUN);
}

void APlayerCharacter::SetActionState(EActionState newState)
{
	ActionState = newState;

	switch (newState) {
	case EActionState::NORMAL:
		GetCharacterMovement()->MaxWalkSpeed = 300;
		break;
	case EActionState::RUN:
		GetCharacterMovement()->MaxWalkSpeed *= 1.3f;
		break;
	case EActionState::ROLL:
	{
		//����� ���� �� �ð��� ���� ��.
		float time = GetMesh()->GetAnimInstance()->Montage_Play(RollMontage, 1.f, EMontagePlayReturnType::Duration);

		FTimerHandle rollTimerHandle;
		FTimerDelegate rollTimerDel = FTimerDelegate::CreateUObject(this, &APlayerCharacter::SetActionState, EActionState::NORMAL);

		GetWorldTimerManager().SetTimer(rollTimerHandle, rollTimerDel, time, false);
	}
		break;
	case EActionState::ATTACK:
		GetMesh()->GetAnimInstance()->Montage_Play(AttackMontage, 1.f, EMontagePlayReturnType::Duration);
		break;
	case EActionState::JUMP:

		break;
	}

}

void APlayerCharacter::Jump()
{
	if (ActionState == EActionState::NORMAL || ActionState == EActionState::RUN)
	{
		Super::Jump();
	}
}

void APlayerCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto weapon = GetWeapon();
	if(weapon!=nullptr)
	{
		weapon->SetOwner(this);
	}
}

