// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnrealClientEnum.h"
#include "Components/TextBlock.h" 
#include "ProtocolLibrary.h"
#include "Components/Image.h"
#include "ProtocolLibrary.h"
#include "UnrealClientCharacter.h"
#include "AllStateWidgetBFL.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API UAllStateWidgetBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(Blueprintcallable, Category="SetNowPVData")// Port8081
	//static void SetNowPVData(KindPV selectedPV);
	static void SetNowPVData(UObject* WorldContextObject, KindPV selectedPV);

	UFUNCTION(Blueprintcallable, Category = "SetGraphViewStatePV") // Port8082
	//static void SetNowPVData(KindPV selectedPV);
	static void SetGraphViewStatePV(UObject* WorldContextObject, KindPV selectedPV);

	UFUNCTION(Blueprintcallable, Category = "SetNowFloorPlanPV") // Port8082
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

	// Image ������ ������ �����ϴ� �Լ�
	UFUNCTION(BlueprintCallable, Category = "WidgetOperations")
	static void SetImageColor(UImage* Image, const FLinearColor& NewColor);
	
	// ���� Image ������ ������ ���������� �����ϴ� �Լ�
	UFUNCTION(BlueprintCallable, Category = "WidgetOperations")
	static void SetImagesColor(const TArray<UImage*>& Images);


	UFUNCTION(BlueprintCallable, Category = "WidgetOperations") //���� �ð� ������Ʈ
	static void UpdateTimeTextBlock(AUnrealClientCharacter* PlayerCharacter, UObject* WorldContextObject, UTextBlock* TextBlock);

	UFUNCTION(BlueprintCallable, Category = "WidgetOperations") // UmgCurrentTime �ʱ�ȭ
	static void InitializeTime();

	UFUNCTION(BlueprintCallable, Category = "WidgetOperations") // 10s ���ϱ�
	static void AddSecondsToCurrentTimePlus(int32 Seconds);

	UFUNCTION(BlueprintCallable, Category = "WidgetOperations") // -10s ���ϱ�
	static void AddSecondsToCurrentTimemin(int32 Seconds);

private:
	static double StartTime;
	static double changeTime; 
};
