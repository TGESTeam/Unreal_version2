// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


// PV�� ������ Ȯ���� �� �ִ� enum
	// DENSITY_MIN�� DENSITY_MAX�� ���ٰ���

UENUM(BlueprintType)
enum KindPV {
	O2 UMETA(DisplayName="O2"),
	CO2 UMETA(DisplayName="CO2"),
	CO UMETA(DisplayName="CO"),
	TEMP UMETA(DisplayName = "TEMP"),
	VELOCITY UMETA(DisplayName = "VELOCITY"),
	ACCEL UMETA(DisplayName = "ACCEL"),
	FUEL UMETA(DisplayName = "FUEL"),
	KIND_PV_LENGTH UMETA(DisplayName = "KIND_PV_LENGTH") // KindPV�� ���̸� ��Ÿ�� �� (�߰� �Ϸ��� ���� ����� �߰��ؾ���)
};

/**
 * 
 */
class UNREALCLIENT_API UnrealClientEnum
{
public:
	UnrealClientEnum();
	~UnrealClientEnum();
};
