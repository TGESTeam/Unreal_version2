// Fill out your copyright notice in the Description page of Project Settings.


#include "AllStateWidgetBFL.h"


void UAllStateWidgetBFL::SetNowPVData(UObject* WorldContextObject, KindPV selectedPV) {

	if (!WorldContextObject) return;

	UWorld* World = WorldContextObject->GetWorld();
	if (!World) return;

	AProtocolLibrary* ProtocolLibraryInstance = AProtocolLibrary::GetInstance(World);


	//O2 UMETA(DisplayName = "O2"),
	//	CO2 UMETA(DisplayName = "CO2"),
	//	CO UMETA(DisplayName = "CO"),
	//	TEMP UMETA(DisplayName = "TEMP"),
	//	VELOCITY UMETA(DisplayName = "VELOCITY"),
	//	ACCEL UMETA(DisplayName = "ACCEL"),
	//	FUEL UMETA(DisplayName = "FUEL"),
	//	KIND_PV_LENGTH UMETA(DisplayName = "KIND_PV_LENGTH") // KindPV의 길이를 나타낸 것 (추가 하려면 이전 멤버에 추가해야함)
	UE_LOG(LogTemp, Log, TEXT("----------------------> SetNowData Opened!!! [%d]"), (int32) selectedPV);

	if (selectedPV == CO2) {
		ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.CO2);
		//if (ProtocolLibraryInstance->port8081Request.CO2 == true)
		//{
		//	ProtocolLibraryInstance->port8081Request.CO2 = false;
		//}
		//else
		//{
		//	ProtocolLibraryInstance->port8081Request.CO2 = true;
		//}
		
		UE_LOG(LogTemp, Log, TEXT("----> Permeate CO2!!"));
	}
	else if(selectedPV == O2){
		ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.O2);

		//if (ProtocolLibraryInstance->port8081Request.O2 == true)
		//{
		//	ProtocolLibraryInstance->port8081Request.O2 = false;
		//}
		//else
		//{
		//	ProtocolLibraryInstance->port8081Request.O2 = true;
		//}

		UE_LOG(LogTemp, Log, TEXT("----> It's safe here!!"));
	}
	else if (selectedPV == CO)
	{
		ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.CO);

		/*if (ProtocolLibraryInstance->port8081Request.CO == true)
		{
			ProtocolLibraryInstance->port8081Request.CO = false;
		}
		else
		{
			ProtocolLibraryInstance->port8081Request.CO = true;
		}*/

	}
	else if (selectedPV == TEMP)
	{
		ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.TEMP);

		//if (ProtocolLibraryInstance->port8081Request.TEMP == true)
		//{
		//	ProtocolLibraryInstance->port8081Request.TEMP = false;
		//}
		//else
		//{
		//	ProtocolLibraryInstance->port8081Request.TEMP = true;
		//}

	}
	else if (selectedPV == VELOCITY)
	{
		ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.VELOCITY);
		//if (ProtocolLibraryInstance->port8081Request.VELOCITY == true)
		//{
		//	ProtocolLibraryInstance->port8081Request.VELOCITY = false;
		//}
		//else
		//{
		//	ProtocolLibraryInstance->port8081Request.VELOCITY = true;
		//}

	}
	else if (selectedPV == ACCEL)
	{
		ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.ACCEL);
		//if (ProtocolLibraryInstance->port8081Request.ACCEL == true)
		//{
		//	ProtocolLibraryInstance->port8081Request.ACCEL = false;
		//}
		//else
		//{
		//	ProtocolLibraryInstance->port8081Request.ACCEL = true;
		//}
	}
	else if (selectedPV == FUEL)
	{
		ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.FUEL);
		//if (ProtocolLibraryInstance->port8081Request.FUEL == true)
		//{
		//	ProtocolLibraryInstance->port8081Request.FUEL = false;
		//}
		//else
		//{
		//	ProtocolLibraryInstance->port8081Request.FUEL = true;
		//}
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
		if (ProtocolLibraryInstance->port8082Request.CO2 == true)
			ProtocolLibraryInstance->port8082Request.CO2 = false;
		else
			ProtocolLibraryInstance->port8082Request.CO2 = true;
	}
	else if (selectedPV == O2)
	{
		if (ProtocolLibraryInstance->port8082Request.O2 == true)
			ProtocolLibraryInstance->port8082Request.O2 = false;
		else
			ProtocolLibraryInstance->port8082Request.O2 = true;
	}
	else if (selectedPV == CO)
	{
		if (ProtocolLibraryInstance->port8082Request.CO == true)
			ProtocolLibraryInstance->port8082Request.CO = false;
		else
			ProtocolLibraryInstance->port8082Request.CO = true;
	}
	else if (selectedPV == TEMP)
	{
		if (ProtocolLibraryInstance->port8082Request.TEMP == true)
			ProtocolLibraryInstance->port8082Request.TEMP = false;
		else
			ProtocolLibraryInstance->port8082Request.TEMP = true;
	}
	else if (selectedPV == VELOCITY)
	{
		if (ProtocolLibraryInstance->port8082Request.VELOCITY == true)
			ProtocolLibraryInstance->port8082Request.VELOCITY = false;
		else
			ProtocolLibraryInstance->port8082Request.VELOCITY = true;
	}
	else if (selectedPV == ACCEL)
	{
		if (ProtocolLibraryInstance->port8082Request.ACCEL == true)
			ProtocolLibraryInstance->port8082Request.ACCEL = false;
		else
			ProtocolLibraryInstance->port8082Request.ACCEL = true;
	}
	else if (selectedPV == FUEL)
	{
		if (ProtocolLibraryInstance->port8082Request.FUEL == true)
			ProtocolLibraryInstance->port8082Request.FUEL = false;
		else
			ProtocolLibraryInstance->port8082Request.FUEL = true;
	}
}

void UAllStateWidgetBFL::SetNowFloorPlanPV(UObject* WorldContextObject, FloorPlanPV selectedPV)
{
	if (!WorldContextObject) return;

	UWorld* World = WorldContextObject->GetWorld();
	if (!World) return;

	AProtocolLibrary* ProtocolLibraryInstance = AProtocolLibrary::GetInstance(World);


	if (selectedPV == X)
	{
		ProtocolLibraryInstance->port8083Request.SetOnlyOneTrue8083(ProtocolLibraryInstance->port8083Request.X);
		UE_LOG(LogTemp, Log, TEXT("----> click X"));
	}
	else if (selectedPV == Y)
	{
		ProtocolLibraryInstance->port8083Request.SetOnlyOneTrue8083(ProtocolLibraryInstance->port8083Request.Y);
		UE_LOG(LogTemp, Log, TEXT("----> click Y"));
	}
	else if (selectedPV == Z)
	{
		ProtocolLibraryInstance->port8083Request.SetOnlyOneTrue8083(ProtocolLibraryInstance->port8083Request.Z);
		UE_LOG(LogTemp, Log, TEXT("----> click Z"));
	}
}

//void UAllStateWidgetBFL::IncreaseValue(int32& CurrentValue)
//{
//	CurrentValue += 10;
//	UE_LOG(LogTemp, Log, TEXT("----> click IncreaseValue"));
//}

int32 UAllStateWidgetBFL::IncreaseValue(int32 CurrentValue)
{
	if (CurrentValue <= 50)
	{
		CurrentValue += 10;
	}
	return CurrentValue;
}

//void UAllStateWidgetBFL::DecreaseValue(int32& CurrentValue)
//{
//	UE_LOG(LogTemp, Log, TEXT("----> Before Decrease: %d"), CurrentValue);
//	CurrentValue -= 10;
//	UE_LOG(LogTemp, Log, TEXT("----> click cur : %d DecreaseValue"), CurrentValue);
//}
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
			
		//// 숫자를 문자열로 변환하고 "s"를 추가
		//FString TextWithSuffix = FString::Printf(TEXT("%ds"), CurrentValue);

		//// FText로 변환하여 SetText에 전달
		//TextBlock->SetText(FText::FromString(TextWithSuffix));

		//UE_LOG(LogTemp, Log, TEXT("----> click in Cur : %d s UpdateTextBlock"), CurrentValue);

	}
	UE_LOG(LogTemp, Log, TEXT("----> click UpdateTextBlock"));
}

void UAllStateWidgetBFL::SetImageColor(UImage* Image, const FLinearColor& NewColor)
{
	if (Image)
	{
		// Image 위젯의 Brush Tint Color를 변경
		Image->SetColorAndOpacity(NewColor);
		UE_LOG(LogTemp, Log, TEXT("----> ho"));
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
