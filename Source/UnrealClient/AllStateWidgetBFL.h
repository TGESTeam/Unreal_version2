// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnrealClientEnum.h"
#include "Components/TextBlock.h" 
#include "ProtocolLibrary.h"
#include "AllStateWidgetBFL.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API UAllStateWidgetBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(Blueprintcallable, Category="SetNowPVData")
	//static void SetNowPVData(KindPV selectedPV);
	static void SetNowPVData(UObject* WorldContextObject, KindPV selectedPV);

	UFUNCTION(Blueprintcallable, Category = "SetNowFloorPlanPV")
	//static void SetNowPVData(KindPV selectedPV);
	static void SetNowFloorPlanPV(UObject* WorldContextObject, FloorPlanPV selectedPV);
	
	// CurrentValue�� ������Ű�� �Լ�
	UFUNCTION(BlueprintCallable, Category = "ValueOperations")
	//static void IncreaseValue(int32& CurrentValue);
	static int32 IncreaseValue(int32 CurrentValue);

	// CurrentValue�� ���ҽ�Ű�� �Լ�
	UFUNCTION(BlueprintCallable, Category = "ValueOperations")
	//static void DecreaseValue(int32& CurrentValue);
	static int32 DecreaseValue(int32 CurrentValue);

	// ���� ���� TextBlock�� ǥ���ϴ� �Լ�
	UFUNCTION(BlueprintCallable, Category = "ValueOperations")
	static void UpdateTextBlock(UObject* WorldContextObject, UTextBlock* TextBlock, int32 CurrentValue);

};
