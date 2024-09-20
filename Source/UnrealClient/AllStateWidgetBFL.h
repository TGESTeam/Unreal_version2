// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnrealClientEnum.h"
#include "Components/TextBlock.h" 
#include "ProtocolLibrary.h"
#include "Components/Image.h"
#include "Components/Widget.h"
#include "ProtocolLibrary.h"
#include "UnrealClientCharacter.h"
#include "Voxel_Color.h"
#include "AllStateWidgetBFL.generated.h"

/**
 *
 */
UCLASS()
class UNREALCLIENT_API UAllStateWidgetBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	/* --------------- [Port 8081] --------------- */
	UFUNCTION(Blueprintcallable, Category = "SetNowPVData")// Port8081
		//static void SetNowPVData(KindPV selectedPV);
		static void SetNowPVData(UObject* WorldContextObject, KindPV selectedPV);

	/* --------------- [Port 8082] --------------- */
	UFUNCTION(Blueprintcallable, Category = "SetGraphViewStatePV") // Port8082
		//static void SetNowPVData(KindPV selectedPV);
		static void SetGraphViewStatePV(UObject* WorldContextObject, KindPV selectedPV);

	UFUNCTION(Blueprintcallable, Category = "SetNowFloorPlanPV") // Port8082
		//static void SetNowPVData(KindPV selectedPV);
		static void SetNowFloorPlanPV(UObject* WorldContextObject, FloorPlanPV selectedPV);

	// FutureTime�� ������Ű�� �Լ�
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

	UFUNCTION(BlueprintCallable, Category = "RequestGraphData")
	static void RequestGraphData(AUnrealClientCharacter* PlayerCharacter, float nowTime); // �ش� �Լ��� ���ؼ� ���� ����

	UFUNCTION(BlueprintCallable, Category = "IsSubscribe")
	static bool IsSubscribe(AUnrealClientCharacter* PlayerCharacter, KindPV selectedPV); // �ش� �Լ��� ���ؼ� ���� ����

	UFUNCTION(BlueprintCallable, Category = "GetCurrentLocationOfDensity")
	static double GetCurrentLocationOfDensity(AUnrealClientCharacter* PlayerCharacter, KindPV selectedPV, float nowTime, bool isBox, int32 index, bool changeToPercent = false);

	UFUNCTION(BlueprintCallable, Category = "GetOnlyCurrentDensity")
	static double GetOnlyCurrentDensity(AUnrealClientCharacter* PlayerCharacter, KindPV selectedPV, float nowTime, bool isBox, int32 index, bool changeToPercent);

	UFUNCTION(BlueprintCallable, Category = "GetCurrentScreenPointCoordinate")
	static FVector2D GetCurrentScreenPointCoordinate(FName SeriesId, UWidget* KantanWidget);

	UFUNCTION(BlueprintCallable, Category="GetThisScreenPointCoordinate")
	static FVector2D GetThisScreenPointCoordinate(UWidget * KantanWidget, FVector2D ThisCoordinate, double RangeOfAxisX, double RagneOfAxisY, bool isFuture);

	UFUNCTION(BlueprintCallable, Category="GetFutureLocationOfDensities")
	static TArray<float> GetFutureLocationOfDensities(int32 PointNum, KindPV SelectedPV, AUnrealClientCharacter* PlayerCharacter, bool changeToPercent);

	UFUNCTION(BlueprintCallable, Category="GetFutureLocationOfDensity")
	static double GetFutureLocationOfDensity(int32 FutureTime, AUnrealClientCharacter * PlayerCharacter, KindPV SelectedPV, bool changeToPercent);

	UFUNCTION(BlueprintCallable, Category = "GetOnlyFutureLocationOfDensity")
	static double GetOnlyFutureLocationOfDensity(int32 FutureTime, AUnrealClientCharacter* PlayerCharacter, KindPV SelectedPV, bool changeToPercent);


	UFUNCTION(BlueprintCallable, Category = "RequestFutureGrpahData")
	static void RequestFutureGrpahData(int32 FutureTime, AUnrealClientCharacter * PlayerCharacter);
	
	UFUNCTION(BlueprintCallable, Category ="ResetGraphIndexs")
	static void ResetGraphIndexs(AUnrealClientCharacter* PlayerCharacter);

	/* --------------- [Port 8083] --------------- */
	// Image ������ ������ �����ϴ� �Լ�
	UFUNCTION(BlueprintCallable, Category = "WidgetOperations")
	static void SetImageColor(UObject* WorldContextObject,UImage* Image, const FLinearColor& NewColor);

	// ���� Image ������ ������ ���������� �����ϴ� �Լ�
	UFUNCTION(BlueprintCallable, Category = "WidgetOperations")
	static void SetImageColorNextBtn(UObject* WorldContextObject, UImage* Image, const FLinearColor& NewColor, int32 index, FloorPlanPV seletedPV);

	static bool CheckResponseAndSetColor(UObject* WorldContextObject, UImage* Image, const FLinearColor& NewColor, int32 index);

	static void MonitorPort8083Answer(UObject* WorldContextObject, UImage* Image, const FLinearColor& NewColor, int32 index);

	UFUNCTION(BlueprintCallable, Category = "WidgetOperations") //���� �ð� ������Ʈ
	static void UpdateTimeTextBlock(AUnrealClientCharacter* PlayerCharacter, UObject* WorldContextObject, UTextBlock* TextBlock);

	UFUNCTION(BlueprintCallable, Category = "GetCurrentTime")
	static double GetCurrentTime();

	UFUNCTION(BlueprintCallable, Category = "WidgetOperations") // UmgCurrentTime �ʱ�ȭ
	static void InitializeTime();

	UFUNCTION(BlueprintCallable, Category = "WidgetOperations") // 10s ���ϱ�
	static void AddSecondsToCurrentTimePlus(int32 Seconds);

	UFUNCTION(BlueprintCallable, Category = "WidgetOperations") // -10s ���ϱ�
	static void AddSecondsToCurrentTimemin(int32 Seconds);


private:
	static double StartTime;
	static double changeTime;
	static int32 indexport8083Answer;
	//static FTimerHandle ColorUpdateTimerHandle;
	static FTimerHandle ZTimerHandle;
	static FTimerHandle YTimerHandle;
	static int32 SetImageColorBtn;
};
