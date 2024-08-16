// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"


// PV의 종류를 확인할 수 있는 enum
	// DENSITY_MIN과 DENSITY_MAX에 접근가능

UENUM(BlueprintType)
enum KindPV {
	O2 UMETA(DisplayName="O2"),
	CO2 UMETA(DisplayName="CO2"),
	CO UMETA(DisplayName="CO"),
	TEMP UMETA(DisplayName = "TEMP"),
	VELOCITY UMETA(DisplayName = "VELOCITY"),
	ACCEL UMETA(DisplayName = "ACCEL"),
	FUEL UMETA(DisplayName = "FUEL"),
	KIND_PV_LENGTH UMETA(DisplayName = "KIND_PV_LENGTH") // KindPV의 길이를 나타낸 것 (추가 하려면 이전 멤버에 추가해야함)
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
