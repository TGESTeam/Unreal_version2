// Fill out your copyright notice in the Description page of Project Settings.


#include "AllStateWidgetBFL.h"
#include "Engine/World.h"

double UAllStateWidgetBFL::StartTime;
double UAllStateWidgetBFL::changeTime;


void UAllStateWidgetBFL::SetNowPVData(UObject* WorldContextObject, KindPV selectedPV) {

	if (!WorldContextObject) return;

	UWorld* World = WorldContextObject->GetWorld();
	if (!World) return;

	AProtocolLibrary* ProtocolLibraryInstance = AProtocolLibrary::GetInstance(World);

	UE_LOG(LogTemp, Log, TEXT("----------------------> SetNowData Opened!!! [%d]"), (int32) selectedPV);
	ProtocolLibraryInstance->setPort8081_requestPVAllFalse();
	if (selectedPV == CO2) {
		//ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.CO2);
		ProtocolLibraryInstance->setPort8081_requestPV((int32)selectedPV, selectedPV);
	}
	else if(selectedPV == O2){
		//ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.O2);
		ProtocolLibraryInstance->setPort8081_requestPV((int32)selectedPV, selectedPV);
	}
	else if (selectedPV == CO)
	{
		//ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.CO);
		ProtocolLibraryInstance->setPort8081_requestPV((int32)selectedPV, selectedPV);
	}
	else if (selectedPV == TEMP)
	{
		//ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.TEMP);
		ProtocolLibraryInstance->setPort8081_requestPV((int32)selectedPV, selectedPV);

	}
	else if (selectedPV == VELOCITY)
	{
		//ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.VELOCITY);
		ProtocolLibraryInstance->setPort8081_requestPV((int32)selectedPV, selectedPV);
	}
	else if (selectedPV == ACCEL)
	{
		//ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.ACCEL);
		ProtocolLibraryInstance->setPort8081_requestPV((int32)selectedPV, selectedPV);
	}
	else if (selectedPV == FUEL)
	{
		//ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.FUEL);
		ProtocolLibraryInstance->setPort8081_requestPV((int32)selectedPV, selectedPV);
	}
	//else if (selectedPV == KIND_PV_LENGTH)
	UE_LOG(LogTemp, Log, TEXT("----> Where is my selectedPV?"));

}

void UAllStateWidgetBFL::SetGraphViewStatePV(UObject* WorldContextObject, KindPV selectedPV)
{

	if (!WorldContextObject) return;

	UWorld* World = WorldContextObject->GetWorld();
	if (!World) return;

	AProtocolLibrary* ProtocolLibraryInstance = AProtocolLibrary::GetInstance(World);

	UE_LOG(LogTemp, Log, TEXT("----------------------> SetNowData Opened!!! [%d]"), (int32)selectedPV);

	if (selectedPV == CO2)
	{
		ProtocolLibraryInstance->setPort8082_request((int32)selectedPV, selectedPV);
		//if (ProtocolLibraryInstance->port8082Request.CO2 == true)
		//	ProtocolLibraryInstance->port8082Request.CO2 = false;
		//else
		//	ProtocolLibraryInstance->port8082Request.CO2 = true;
	}
	else if (selectedPV == O2)
	{
		//if (ProtocolLibraryInstance->port8082Request.O2 == true)
		//	ProtocolLibraryInstance->port8082Request.O2 = false;
		//else
		//	ProtocolLibraryInstance->port8082Request.O2 = true;
		ProtocolLibraryInstance->setPort8082_request((int32)selectedPV, selectedPV);
	}
	else if (selectedPV == CO)
	{
		//if (ProtocolLibraryInstance->port8082Request.CO == true)
		//	ProtocolLibraryInstance->port8082Request.CO = false;
		//else
		//	ProtocolLibraryInstance->port8082Request.CO = true;
		ProtocolLibraryInstance->setPort8082_request((int32)selectedPV, selectedPV);
	}
	else if (selectedPV == TEMP)
	{
		//if (ProtocolLibraryInstance->port8082Request.TEMP == true)
		//	ProtocolLibraryInstance->port8082Request.TEMP = false;
		//else
		//	ProtocolLibraryInstance->port8082Request.TEMP = true;
		ProtocolLibraryInstance->setPort8082_request((int32)selectedPV, selectedPV);
	}
	else if (selectedPV == VELOCITY)
	{
		//if (ProtocolLibraryInstance->port8082Request.VELOCITY == true)
		//	ProtocolLibraryInstance->port8082Request.VELOCITY = false;
		//else
		//	ProtocolLibraryInstance->port8082Request.VELOCITY = true;
		ProtocolLibraryInstance->setPort8082_request((int32)selectedPV, selectedPV);
	}
	else if (selectedPV == ACCEL)
	{
		//if (ProtocolLibraryInstance->port8082Request.ACCEL == true)
		//	ProtocolLibraryInstance->port8082Request.ACCEL = false;
		//else
		//	ProtocolLibraryInstance->port8082Request.ACCEL = true;
		ProtocolLibraryInstance->setPort8082_request((int32)selectedPV, selectedPV);
	}
	else if (selectedPV == FUEL)
	{
		//if (ProtocolLibraryInstance->port8082Request.FUEL == true)
		//	ProtocolLibraryInstance->port8082Request.FUEL = false;
		//else
		//	ProtocolLibraryInstance->port8082Request.FUEL = true;
		ProtocolLibraryInstance->setPort8082_request((int32)selectedPV, selectedPV);
	}
}

void UAllStateWidgetBFL::SetNowFloorPlanPV(UObject* WorldContextObject, FloorPlanPV selectedPV)
{
	if (!WorldContextObject) return;

	UWorld* World = WorldContextObject->GetWorld();
	if (!World) return;

	AProtocolLibrary* ProtocolLibraryInstance = AProtocolLibrary::GetInstance(World);

	ProtocolLibraryInstance->setPort8083_requestPVAllFalse();
	if (selectedPV == X)
	{
		ProtocolLibraryInstance->setPort8083_request((int32)selectedPV, selectedPV);
		//ProtocolLibraryInstance->port8083Request.SetOnlyOneTrue8083(ProtocolLibraryInstance->port8083Request.X);
		UE_LOG(LogTemp, Log, TEXT("----> click X"));
	}
	else if (selectedPV == Y)
	{
		ProtocolLibraryInstance->setPort8083_request((int32)selectedPV, selectedPV);
		//ProtocolLibraryInstance->port8083Request.SetOnlyOneTrue8083(ProtocolLibraryInstance->port8083Request.Y);
		UE_LOG(LogTemp, Log, TEXT("----> click Y"));
	}
	else if (selectedPV == Z)
	{
		ProtocolLibraryInstance->setPort8083_request((int32)selectedPV, selectedPV);
		//ProtocolLibraryInstance->port8083Request.SetOnlyOneTrue8083(ProtocolLibraryInstance->port8083Request.Z);
		UE_LOG(LogTemp, Log, TEXT("----> click Z"));
	}
}


int32 UAllStateWidgetBFL::IncreaseValue(int32 CurrentValue)
{
	if (CurrentValue <= 50)
	{
		CurrentValue += 10;
	}
	return CurrentValue;
}

int32 UAllStateWidgetBFL::DecreaseValue(int32 CurrentValue)
{
	if (CurrentValue > 0)
	{
		CurrentValue -= 10;
	}
	
	return CurrentValue;
}

void UAllStateWidgetBFL::UpdateTextBlock(UObject* WorldContextObject, UTextBlock* TextBlock, int32 CurrentValue)
{

	if (TextBlock)
	{
		if (!WorldContextObject) return;

		UWorld* World = WorldContextObject->GetWorld();
		if (!World) return;

		AProtocolLibrary* ProtocolLibraryInstance = AProtocolLibrary::GetInstance(World);
		ProtocolLibraryInstance->PredictTime = CurrentValue;
		UE_LOG(LogTemp, Log, TEXT("----> click in ProtocolLibraryInstance : %d UpdateTextBlock"), ProtocolLibraryInstance->PredictTime);

		TextBlock->SetText(FText::AsNumber(CurrentValue));
		UE_LOG(LogTemp, Log, TEXT("----> click in Cur : %d UpdateTextBlock"), CurrentValue);

	}
	UE_LOG(LogTemp, Log, TEXT("----> click UpdateTextBlock"));
}

void UAllStateWidgetBFL::SetImageColor(UImage* Image, const FLinearColor& NewColor)
{
	if (Image)
	{
		// Image 위젯의 Brush Tint Color를 변경
		Image->SetColorAndOpacity(NewColor);
	}
}

void UAllStateWidgetBFL::SetImagesColor(const TArray<UImage*>& Images)
{
	FLinearColor RedColor = FLinearColor::Red;  // 빨간색 정의

	// 배열에 있는 모든 Image 위젯의 색상을 빨간색으로 변경
	for (UImage* Image : Images)
	{
		if (Image)
		{
			Image->SetColorAndOpacity(RedColor);
		}
	}
}

void UAllStateWidgetBFL::UpdateTimeTextBlock(AUnrealClientCharacter* PlayerCharacter, UObject* WorldContextObject, UTextBlock* TextBlock)
{
	if (PlayerCharacter == nullptr) {
		UE_LOG(LogTemp, Log, TEXT("Player Character is null!"));
		return;
	}
	AProtocolLibrary* ProtocolLibraryInstance = PlayerCharacter->GetProtocolLibrary();
	if (ProtocolLibraryInstance == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("Player Character is null!"));
		return;
	}



	// 현재 시간을 초 단위로 계산, changeTime을 더함
	double CurrentTimeInSeconds = FPlatformTime::Seconds() - StartTime + changeTime;

	if (CurrentTimeInSeconds < 0)
	{
		CurrentTimeInSeconds = 0.0;
		StartTime = FPlatformTime::Seconds();
		changeTime = 0.0;
	}

	FTimespan TimeSinceStartSpan = FTimespan::FromSeconds(CurrentTimeInSeconds);

	FTimespan AdjustedTimeSpan = TimeSinceStartSpan ;

	int32 Hours = AdjustedTimeSpan.GetHours();
	int32 Minutes = AdjustedTimeSpan.GetMinutes();
	int32 Seconds = AdjustedTimeSpan.GetSeconds();
	int32 Milliseconds = static_cast<int32>(AdjustedTimeSpan.GetTotalMilliseconds()) % 1000;


	FString TimeString = FString::Printf(TEXT("%02d:%02d:%02d.%03d"), Hours, Minutes, Seconds, Milliseconds);
	TextBlock->SetText(FText::FromString(TimeString));
	ProtocolLibraryInstance->CurrentTime = AdjustedTimeSpan;
}

void UAllStateWidgetBFL::InitializeTime()
{

	StartTime = FPlatformTime::Seconds();
	changeTime = 0.0f;
}



void UAllStateWidgetBFL::AddSecondsToCurrentTimePlus(int32 Seconds)
{
	changeTime += 10.0;
}

void UAllStateWidgetBFL::AddSecondsToCurrentTimemin(int32 Seconds)
{
	changeTime -= 10.0;
}


