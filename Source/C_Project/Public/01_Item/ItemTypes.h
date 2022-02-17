// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemTypes.generated.h"


USTRUCT(BluprintType)
struct FItemInformation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) // �̹���
		class UTexture2D* Item_Image;



	UPROPERTY(EditAnywhere) // �̸�
		FString Item_Name;;



	UPROPERTY(EditAnywhere) // ����
		FString Item_Description;

	UPROPERTY(EditAnywhere) // ����_long
		FString Item_Description_Long;



	UPROPERTY() // ����
		int32 item_Count;
	
	UPROPERTY(EditAnywhere) // ����
		int32 item_Price;
};



USTRUCT(BluprintType)
struct FEquipment : public FItemInformation
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float damage;
	UPROPERTY(EditAnywhere)
		float defence;

	UPROPERTY(EditAnywhere)
		float ActionSpeed;

	UPROPERTY(EditAnywhere)
		int32 Str;
	UPROPERTY(EditAnywhere)
		int32 Dex;
	UPROPERTY(EditAnywhere)
		int32 Wiz;

	UPROPERTY(EditAnywhere)
		float MaxHP;
	UPROPERTY(EditAnywhere)
		float MaxMP;
	UPROPERTY(EditAnywhere)
		float MaxSP;
};



USTRUCT(BluprintType)
struct FWeapon : public FEquipment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) // ������ ����
		class UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere) // ������ �ִϸ��̼�
		class UAnimBluprint* AnimBluprint;
}


USTRUCT(BluprintType)
struct FShield : public FEquipment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) // ������ ����
		class UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere) // ������ �ִϸ��̼�
		class UAnimBluprint* AnimBluprint;
}



USTRUCT(BluprintType)
struct FGlove : public FEquipment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) // ������ ����
		class UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere) // ������ �ִϸ��̼�
		class UAnimBluprint* AnimBluprint;
}
USTRUCT(BluprintType)
struct FBlet : public FEquipment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) // ������ ����
		class UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere) // ������ �ִϸ��̼�
		class UAnimBluprint* AnimBluprint;
}
USTRUCT(BluprintType)
struct FHelmet : public FEquipment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) // ������ ����
		class UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere) // ������ �ִϸ��̼�
		class UAnimBluprint* AnimBluprint;
}
USTRUCT(BluprintType)
struct FShoes : public FEquipment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) // ������ ����
		class UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere) // ������ �ִϸ��̼�
		class UAnimBluprint* AnimBluprint;
}
USTRUCT(BluprintType)
struct FShoulder : public FEquipment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere) // ������ ����
		class UStaticMesh* Mesh;
	UPROPERTY(EditAnywhere) // ������ �ִϸ��̼�
		class UAnimBluprint* AnimBluprint;
}






USTRUCT(BluprintType)
struct FPotion : public FEquipment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere)
		float add_damage;
	UPROPERTY(EditAnywhere)
		float add_defence;

	UPROPERTY(EditAnywhere)
		float add_ActionSpeed;

	UPROPERTY(EditAnywhere)
		int32 add_Str;
	UPROPERTY(EditAnywhere)
		int32 add_Dex;
	UPROPERTY(EditAnywhere)
		int32 add_Wiz;

	UPROPERTY(EditAnywhere)
		float add_MaxHP;
	UPROPERTY(EditAnywhere)
		float add_MaxMP;
	UPROPERTY(EditAnywhere)
		float add_MaxSP;

	UPROPERTY(EditAnywhere)
		float add_HP;
	UPROPERTY(EditAnywhere)
		float add_MP;
	UPROPERTY(EditAnywhere)
		float add_SP;
};

/**
 * 
 */
UCLASS()
class C_PROJECT_API UItemTypes : public UObject
{
	GENERATED_BODY()
	
};
