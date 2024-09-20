// Fill out your copyright notice in the Description page of Project Settings.


#include "AllStateWidgetBFL.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

double UAllStateWidgetBFL::StartTime;
double UAllStateWidgetBFL::changeTime;
int UAllStateWidgetBFL::indexport8083Answer;
FTimerHandle UAllStateWidgetBFL::ZTimerHandle;
FTimerHandle UAllStateWidgetBFL::YTimerHandle;
int32 UAllStateWidgetBFL::SetImageColorBtn;

void UAllStateWidgetBFL::SetNowPVData(UObject* WorldContextObject, KindPV selectedPV) {

	if (!WorldContextObject) return;

	UWorld* World = WorldContextObject->GetWorld();
	if (!World) return;

	AProtocolLibrary* ProtocolLibraryInstance = AProtocolLibrary::GetInstance(World);


	UE_LOG(LogTemp, Log, TEXT("----------------------> SetNowData Opened!!! [%d]"), (int32)selectedPV);
	ProtocolLibraryInstance->setPort8081_requestPVAllFalse();
	if (selectedPV == CO2) {
		//ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.CO2);
		ProtocolLibraryInstance->setPort8081_requestPV((int32)selectedPV, selectedPV);
	}
	else if (selectedPV == O2) {
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

void UAllStateWidgetBFL::SetImageColor(UObject* WorldContextObject, UImage* Image, const FLinearColor& NewColor)
{
	if (Image)
	{
		// NewColor 값을 로그로 출력 LogTemp: NewColor: R=1.000000, G=0.000000, B=0.000000, A=1.000000
		//UE_LOG(LogTemp, Log, TEXT("NewColor: R=%f, G=%f, B=%f, A=%f"), NewColor.R, NewColor.G, NewColor.B, NewColor.A);

		if (!WorldContextObject) return;

		UWorld* World = WorldContextObject->GetWorld();
		if (!World) return;

		AProtocolLibrary* ProtocolLibraryInstance = AProtocolLibrary::GetInstance(World);

		Image->SetColorAndOpacity(NewColor);

	} 
}

void UAllStateWidgetBFL::SetImageColorNextBtn(UObject* WorldContextObject, UImage* Image, const FLinearColor& NewColor, int32 index, FloorPlanPV seletedPV)
{
	if (!Image || !WorldContextObject) return;

	UWorld* World = WorldContextObject->GetWorld();
	if (!World) return;

	AProtocolLibrary* ProtocolLibraryInstance = AProtocolLibrary::GetInstance(World);
	if (!ProtocolLibraryInstance) return;

	if (SetImageColorBtn >= 10000)
	{
		return;
	}

	ProtocolLibraryInstance->shouldTriggerEvent = true;

	// 타이머를 사용하여 주기적으로 비동기 작업 수행
	FTimerHandle TimerHandle;
	World->GetTimerManager().SetTimer(
		TimerHandle,
		[WorldContextObject, Image, NewColor, index]()
	{
		// 백그라운드 스레드에서 필요한 작업 수행
		AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [WorldContextObject, Image, NewColor, index]()
		{
			//UE_LOG(LogTemp, Log, TEXT("DEBUG : AsyncTask %d"), index);

			UAllStateWidgetBFL::MonitorPort8083Answer(WorldContextObject, Image, NewColor, index);
		});
	},
		0.2f,
		true 
	);

	SetImageColorBtn++;
}


void UAllStateWidgetBFL::MonitorPort8083Answer(UObject* WorldContextObject, UImage* Image, const FLinearColor& NewColor, int32 index)
{
	if (!WorldContextObject || !Image) return;

	UWorld* World = WorldContextObject->GetWorld();
	if (!World) return;

	AProtocolLibrary* ProtocolLibraryInstance = AProtocolLibrary::GetInstance(World);
	if (!ProtocolLibraryInstance) return;

	{
		FScopeLock Lock(&ProtocolLibraryInstance->Mutex); 
		if (!ProtocolLibraryInstance->port8083Answer.IsEmpty())
		{
			//UE_LOG(LogTemp, Log, TEXT("DEBUG : MonitorPort8083Answer"));
			UAllStateWidgetBFL::CheckResponseAndSetColor(WorldContextObject, Image, NewColor, index);

			ProtocolLibraryInstance->CompletedIterations++; 

			if (ProtocolLibraryInstance->CompletedIterations >= AProtocolLibrary::MaxIterations)
			{
				ProtocolLibraryInstance->CompletedIterations = 0; 
				ProtocolLibraryInstance->port8083Answer.RemoveAt(0, 10000, false); 
			}
		}
	}
}

bool UAllStateWidgetBFL::CheckResponseAndSetColor(UObject* WorldContextObject, UImage* Image, const FLinearColor& NewColor, int32 index)
{
	if (!WorldContextObject || !Image) return false;

	UWorld* World = WorldContextObject->GetWorld();
	if (!World) return false;

	AProtocolLibrary* ProtocolLibraryInstance = AProtocolLibrary::GetInstance(World);
	if (!ProtocolLibraryInstance) return false;

	FScopeLock Lock(&ProtocolLibraryInstance->Mutex2); // 잠금 추가

	if (ProtocolLibraryInstance->port8083Answer.IsValidIndex(index))
	{
		//UE_LOG(LogTemp, Log, TEXT("DEBUG : CheckResponseAndSetColor"));
		double firstElement = ProtocolLibraryInstance->port8083Answer[index];

		FLinearColor KindPVColor = ProtocolLibraryInstance->GetLienarColor(firstElement, ProtocolLibraryInstance->SelectedValue);

		if (Image->ColorAndOpacity != KindPVColor)
		{
			AsyncTask(ENamedThreads::GameThread, [Image, KindPVColor]()
			{
				if (Image)
				{
					Image->SetColorAndOpacity(KindPVColor);
				}
			});
		}

		return false;  // 색상이 변경되었으므로 반복 중지
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("DEBUG : CheckResponseAndSetColor2"));
		AsyncTask(ENamedThreads::GameThread, [Image, NewColor]()
		{
			if (Image && Image->ColorAndOpacity != NewColor)
			{
				Image->SetColorAndOpacity(NewColor);
			}
		});
	}

	return false;  // 색상이 변경되지 않았으므로 반복 계속
}




// ---- 최종 ----
//void UAllStateWidgetBFL::SetImageColorNextBtn(UObject* WorldContextObject, UImage* Image, const FLinearColor& NewColor, int32 index, FloorPlanPV seletedPV)
//{
//
//	if (!Image || !WorldContextObject) return;
//
//	UWorld* World = WorldContextObject->GetWorld();
//	if (!World) return;
//
//	AProtocolLibrary* ProtocolLibraryInstance = AProtocolLibrary::GetInstance(World);
//	if (!ProtocolLibraryInstance) return;
//
//	if (SetImageColorBtn >= 10000 )
//	{
//		return;
//	}
//	ProtocolLibraryInstance->shouldTriggerEvent = true;
//	
//	//UE_LOG(LogTemp, Log, TEXT("DEBUG : SetImageColorNextBtn"));
//	//UE_LOG(LogTemp, Log, TEXT("button SetImageColorBtn. %d"), SetImageColorBtn);
//	//else if (SetImageColorBtn != -1 && bButtonPressed)
//	//{
//	//	return; 
//	//}
//	//UE_LOG(LogTemp, Log, TEXT("----> click UpdateTextBlock"));
//	
//	
//	// 버튼이 이미 눌린 상태라면 함수 실행 중단
//	//if (bButtonPressed && index == 9999)
//	//{
//	//	UE_LOG(LogTemp, Log, TEXT("button pressed."));
//	//	return;
//	//}
//	
//	FTimerHandle TimerHandle;
//	//if (World->GetTimerManager().IsTimerActive(TimerHandle))
//	//{
//	//	// Z 타이머가 이미 활성 상태라면 아래 코드를 실행하지 않음
//	//	UE_LOG(LogTemp, Log, TEXT("Zstop Timer"));
//	//	return;
//	//}
//
//	//UE_LOG(LogTemp, Log, TEXT("----> SetImageColorNextBtn : %d ---> %d"), index, (int32) seletedPV);
//	// 타이머 핸들 생성
//
//	World->GetTimerManager().SetTimer(
//		TimerHandle,
//		[WorldContextObject, Image, NewColor, &TimerHandle, index]()
//	{
//		// 주기적으로 port8083Answer 값을 감시
//		UAllStateWidgetBFL::MonitorPort8083Answer(WorldContextObject, Image, NewColor, index);
//	},
//		0.98765f, // 1초마다 감시
//		true  // 반복 실행
//	);
//
//	//SetImageColorBtn++;
//	//ProtocolLibraryInstance->checkSetImageColorBtn++;
//	SetImageColorBtn++;
//
//}
//
//
//void UAllStateWidgetBFL::MonitorPort8083Answer(UObject* WorldContextObject, UImage* Image, const FLinearColor& NewColor, int32 index)
//{
//	if (!WorldContextObject || !Image) return;
//
//	UWorld* World = WorldContextObject->GetWorld();
//	if (!World) return;
//
//	AProtocolLibrary* ProtocolLibraryInstance = AProtocolLibrary::GetInstance(World);
//	if (!ProtocolLibraryInstance) return;
//
//	// port8083Answer의 길이가 10,000이 될 때까지 대기
//	//ProtocolLibraryInstance->AnswerSizeReachedEvent->Wait();
//
//	// Critical section 시작
//	{
//		FScopeLock Lock(&ProtocolLibraryInstance->Mutex); // 잠금
//		if (!ProtocolLibraryInstance->port8083Answer.IsEmpty())
//		{
//			//UE_LOG(LogTemp, Log, TEXT("DEBUG : MonitorPort8083Answer out : %d"), index);
//			UAllStateWidgetBFL::CheckResponseAndSetColor(WorldContextObject, Image, NewColor, index);
//
//			ProtocolLibraryInstance->CompletedIterations++; // 순회 완료 카운터 증가
//
//			if (ProtocolLibraryInstance->CompletedIterations >= AProtocolLibrary::MaxIterations)
//			{
//				ProtocolLibraryInstance->CompletedIterations = 0; // 카운터 초기화
//				ProtocolLibraryInstance->port8083Answer.RemoveAt(0, 10000, false); // port8083Answer 초기화
//				//UE_LOG(LogTemp, Log, TEXT("DEBUG : All iterations complete, resetting arrays."));
//			}
//		}
//	} // 잠금 해제
//}
//
//
//
//
//bool UAllStateWidgetBFL::CheckResponseAndSetColor(UObject* WorldContextObject, UImage* Image, const FLinearColor& NewColor, int32 index)
//{
//	if (!WorldContextObject || !Image) return false;
//
//	UWorld* World = WorldContextObject->GetWorld();
//	if (!World) return false;
//
//	AProtocolLibrary* ProtocolLibraryInstance = AProtocolLibrary::GetInstance(World);
//	if (!ProtocolLibraryInstance) return false;
//
//	FScopeLock Lock(&ProtocolLibraryInstance->Mutex2); // 잠금 추가
//
//	if (ProtocolLibraryInstance->port8083Answer.IsValidIndex(index))
//	{
//		//UE_LOG(LogTemp, Log, TEXT("DEBUG : CheckResponseAndSetColor IsValidIndex : %d"), index);
//
//		double firstElement = ProtocolLibraryInstance->port8083Answer[index];
//		//UE_LOG(LogTemp, Log, TEXT("DEBUG : CheckResponseAndSetColor firstElement : %lf"), firstElement);
//
//		FLinearColor KindPVColor = ProtocolLibraryInstance->GetLienarColor(firstElement, ProtocolLibraryInstance->SelectedValue);
//
//		if (Image->ColorAndOpacity != KindPVColor)
//		{
//			//UE_LOG(LogTemp, Log, TEXT("DEBUG : CheckResponseAndSetColor Image->ColorAndOpacity in "));
//			Image->SetColorAndOpacity(KindPVColor);
//			//UE_LOG(LogTemp, Log, TEXT("DEBUG : CheckResponseAndSetColor Image->ColorAndOpacity out "));
//		}
//
//		return false;  // 색상이 변경되었으므로 반복 중지
//	}
//	else
//	{
//		if (Image->ColorAndOpacity != NewColor)
//		{
//			Image->SetColorAndOpacity(NewColor);
//		}
//	}
//
//	return false;  // 색상이 변경되지 않았으므로 반복 계속
//}


//-------------------------------

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
	//UE_LOG(LogTemp, Log, TEXT("changeTime : %lf"), changeTime);
	if (CurrentTimeInSeconds < 0)
	{
		CurrentTimeInSeconds = 0.0;
		StartTime = FPlatformTime::Seconds();
		changeTime = 0.0;
	}

	FTimespan TimeSinceStartSpan = FTimespan::FromSeconds(CurrentTimeInSeconds);

	FTimespan AdjustedTimeSpan = TimeSinceStartSpan;

	int32 Hours = AdjustedTimeSpan.GetHours();
	int32 Minutes = AdjustedTimeSpan.GetMinutes();
	int32 Seconds = AdjustedTimeSpan.GetSeconds();
	int32 Milliseconds = static_cast<int32>(AdjustedTimeSpan.GetTotalMilliseconds()) % 1000;


	FString TimeString = FString::Printf(TEXT("%02d:%02d:%02d.%03d"), Hours, Minutes, Seconds, Milliseconds);
	TextBlock->SetText(FText::FromString(TimeString));
	ProtocolLibraryInstance->CurrentTime = AdjustedTimeSpan;
}

double UAllStateWidgetBFL::GetCurrentTime()
{
	double CurrentTimeInSeconds = FPlatformTime::Seconds() - StartTime + changeTime;
	//UE_LOG(LogTemp, Log, TEXT("changeTime : %lf"), changeTime);
	if (CurrentTimeInSeconds < 0)
	{
		CurrentTimeInSeconds = 0.0;
		StartTime = FPlatformTime::Seconds();
		changeTime = 0.0;
	}

	FTimespan TimeSinceStartSpan = FTimespan::FromSeconds(CurrentTimeInSeconds);

	
	//return TimeSinceStartSpan.GetTotalSeconds();
	//return FMath::RoundToDouble(TimeSinceStartSpan.GetTotalSeconds());
	double TotalSeconds = TimeSinceStartSpan.GetTotalSeconds();
	double RoundedToHalf = FMath::RoundToDouble(TotalSeconds * 2.0) / 2.0;
	return RoundedToHalf;
}

void UAllStateWidgetBFL::InitializeTime()
{

	StartTime = FPlatformTime::Seconds();
	changeTime = 0.0f;
	indexport8083Answer = 0;
	SetImageColorBtn = 0;
}



void UAllStateWidgetBFL::AddSecondsToCurrentTimePlus(int32 Seconds)
{
	changeTime = changeTime + Seconds;
}

void UAllStateWidgetBFL::AddSecondsToCurrentTimemin(int32 Seconds)
{
	changeTime = changeTime + Seconds;;
}


void UAllStateWidgetBFL::RequestGraphData(AUnrealClientCharacter* PlayerCharacter, float nowTime) {
	/*
		nowTime을 기반으로 서버에 요청하고, 값을 받았다고 가정함
	*/
	FString Message = TEXT("");
	if (PlayerCharacter == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not found the Player Character!"));
		return;
	}

	AProtocolLibrary* Instance = PlayerCharacter->GetProtocolLibrary();
	if (Instance == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not exist the character's ProtocolLibraryInstance!"));
		return;
	}

	//Instance->port8082Request;

	// (TEST) 작성된 메세지
	Message.Append("KI");
	for (size_t i = 0; i < Instance->Port8082_request.Num(); i++)
	{
		Message.Append(Instance->Port8082_request[i] ? TEXT("1") : TEXT("0"));
	}
	//Message.Append(Instance->port8082Request.CO2 ? TEXT("1") : TEXT("0"));
	//Message.Append(Instance->port8082Request.O2 ? TEXT("1") : TEXT("0"));
	//Message.Append(Instance->port8082Request.CO ? TEXT("1") : TEXT("0"));
	//Message.Append(Instance->port8082Request.TEMP ? TEXT("1") : TEXT("0"));
	//Message.Append(Instance->port8082Request.VELOCITY ? TEXT("1") : TEXT("0"));
	//Message.Append(Instance->port8082Request.ACCEL ? TEXT("1") : TEXT("0"));
	//Message.Append(Instance->port8082Request.FUEL ? TEXT("1") : TEXT("0"));

	// (TEST) 허용된 값에 따라 value 채우기
	for (size_t i = 0; i < Instance->Port8082_request.Num(); i++)
	{
		Message.Append(Instance->Port8082_request[i] ? TEXT("1") : TEXT("0"));
	}

	for (size_t i = 0; i < Instance->Port8082_request.Num(); i++) {
		if (Instance->Port8082_request[i]) {
			PlayerCharacter->CurrentLocationStatus[i] = FMath::RandRange(0.5f, 1.0f);
		}
	}
}

bool UAllStateWidgetBFL::IsSubscribe(AUnrealClientCharacter* PlayerCharacter, KindPV selectedPV) {
	FString Message = TEXT("");
	if (PlayerCharacter == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not found the Player Character!!"));
		return false;
	}

	AProtocolLibrary* Instance = PlayerCharacter->GetProtocolLibrary();
	if (Instance == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not exist the character's ProtocolLibraryInstance!"));
		return false;
	}

	bool isSubscribe = Instance->Port8082_request[selectedPV];

	return isSubscribe;
}

// 재윤
//double UAllStateWidgetBFL::GetCurrentLocationOfDensity(AUnrealClientCharacter* PlayerCharacter, KindPV selectedPV, float nowTime, bool isBox, int32 index, bool changeToPercent) {
//	if (PlayerCharacter == nullptr) {
//		UE_LOG(LogTemp, Error, TEXT("Not found the Player Character!"));
//		return 0.0f;
//	}
//	UE_LOG(LogTemp, Error, TEXT("ResponseBuffer index %d"), (int32)selectedPV);
//	//FScopeLock Lock(&PlayerCharacter->GetProtocolLibrary()->CriticalSection);
//	//if (PlayerCharacter->GetProtocolLibrary()->ResponseBuffer.Num() == 0) {
//	//	UE_LOG(LogTemp, Error, TEXT("ResponseBuffer is empty!"));
//	//	return 0.0f;
//	//}		
//
//	return 0.0f;
//
//	//// 최신 응답 데이터를 버퍼에서 가져옴
//	//TArray<double> latestResponse = PlayerCharacter->GetProtocolLibrary()->ResponseBuffer.Last();
//	//UE_LOG(LogTemp, Error, TEXT("ResponseBuffer index %d"), index);
//	//if (latestResponse.IsValidIndex(index)) {
//	//	double density = latestResponse[index];
//
//	//	// 퍼센트로 변환해야 할 경우
//	//	if (changeToPercent) {
//	//		double densityPercent = (density - AVoxel_Color::DENSITY_MIN[selectedPV]) / (AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV]) * 100;
//	//		return densityPercent;
//	//	}
//
//	//	return density;
//	//}
//
//	//return 0.0;
//}


//double UAllStateWidgetBFL::GetCurrentLocationOfDensity(AUnrealClientCharacter* PlayerCharacter, KindPV selectedPV, float nowTime, bool isBox, int32 index, bool changeToPercent) {
//		UE_LOG(LogTemp, Log, TEXT("Count : %d "), index);
//	
//		if (PlayerCharacter == nullptr) {
//			UE_LOG(LogTemp, Error, TEXT("Not found the Player Character!"));
//			return false;
//		}
//		//UE_LOG(LogTemp, Error, TEXT("selectedPV : %d"), (int32) selectedPV);
//		double density = 0.0f;
//		UE_LOG(LogTemp, Error, TEXT("GetCurrentLocationOfDensity index :  %d"), index);
//	
//		// 배열이 비어 있거나 ThisCnt가 유효하지 않으면 바로 반환
//		if (PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer.Num() == 0) {
//			UE_LOG(LogTemp, Error, TEXT("port8082ResponseAnswer is empty!"));
//			return 0.0f;
//		}
//
//
//	
//		//예측 시간이 0일 경우
//		if (PlayerCharacter->GetProtocolLibrary()->PredictTime == 0) {
//	
//			if (!PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer.IsEmpty()) {
//				FScopeLock Lock(&PlayerCharacter->GetProtocolLibrary()->CriticalSection);  // CriticalSection으로 배열 접근 동기화
//				//density = PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer[ThisCnt];
//				//UE_LOG(LogTemp, Error, TEXT("GetCurrentLocationOfDensity %lf") , density);
//			}
//		}
//	
//		
//		if (changeToPercent) {
//	
//			//UE_LOG(LogTemp, Log, TEXT("0 : %lf, 1 : %lf, 2 : %lf, 3 : %lf , 4 : %lf , 5 : %lf , 6 : %lf"),  AVoxel_Color::DENSITY_MIN[0], AVoxel_Color::DENSITY_MIN[1], AVoxel_Color::DENSITY_MIN[2], AVoxel_Color::DENSITY_MIN[3], AVoxel_Color::DENSITY_MIN[4], AVoxel_Color::DENSITY_MIN[5], AVoxel_Color::DENSITY_MIN[6]);
//	
//			double densityPercent = (density - AVoxel_Color::DENSITY_MIN[selectedPV]) / (AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV]) * 100;
//			//UE_LOG(LogTemp, Log, TEXT("[%d]Percent Data: %lf | density: %lf"), (int32)selectedPV, densityPercent, density);
//			//UE_LOG(LogTemp, Log, TEXT("selected : [%d], density: %lf, DENSITY_MIN[selectedPV] : %lf, DENSITY_MAX[selectedPV : %lf,  Percent Data: %lf "), (int32)selectedPV, density, AVoxel_Color::DENSITY_MIN[selectedPV], AVoxel_Color::DENSITY_MAX[selectedPV] , densityPercent );
//			//UE_LOG(LogTemp, Log, TEXT("AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV] : [%lf], "), AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV]);
//			//UE_LOG(LogTemp, Log, TEXT("density - AVoxel_Color::DENSITY_MIN[selectedPV] : [%lf], "), density - AVoxel_Color::DENSITY_MIN[selectedPV]);
//			if (densityPercent > 1.0f) {
//				return 1.0f;
//			}
//			else if (densityPercent < 0.0f) {
//				return 0.0f;
//			}
//			
//			return densityPercent;
//		}
//	
//		/* 중요) 나중에 MIn과 MAX에 대하여 Persent를 구해야함 */
//		//float densityPercent;
//	
//		return density;
//}


// ------ 최신 =
double UAllStateWidgetBFL::GetOnlyCurrentDensity(AUnrealClientCharacter* PlayerCharacter, KindPV selectedPV, float nowTime, bool isBox, int32 index, bool changeToPercent) {
	if (PlayerCharacter == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not found the Player Character!"));
		return false;
	}
	//UE_LOG(LogTemp, Error, TEXT("selectedPV : %d"), (int32)selectedPV);
	double density = 0.0f;

	if (selectedPV == CO2) {
		{
			//FScopeLock Lock(&PlayerCharacter->GetProtocolLibrary()->CriticalSectionCO2_Current); // O2_Current 배열에 대한 뮤텍스
			//if (PlayerCharacter->GetProtocolLibrary()->Co2_Current.Num() > 0) {
			//	density = PlayerCharacter->GetProtocolLibrary()->Co2_Current[0];
			//	PlayerCharacter->GetProtocolLibrary()->Co2_Current.RemoveAt(0);
			//}
			//else {
			//	//UE_LOG(LogTemp, Error, TEXT("O2_Current array is empty"));
			//}
		}
	}
	else if (selectedPV == O2) {
		{
			//FScopeLock Lock(&PlayerCharacter->GetProtocolLibrary()->CriticalSectionO2_Current); // O2_Current 배열에 대한 뮤텍스
			//if (PlayerCharacter->GetProtocolLibrary()->O2_Current.Num() > 0) {
			//	density = PlayerCharacter->GetProtocolLibrary()->O2_Current[0];
			//	PlayerCharacter->GetProtocolLibrary()->O2_Current.RemoveAt(0);
			//}
			//else {
			//	//UE_LOG(LogTemp, Error, TEXT("O2_Current array is empty"));
			//}
		}
	}
	//else if (selectedPV == CO) {
	//	{
	//		FScopeLock Lock(&PlayerCharacter->GetProtocolLibrary()->CriticalSectionCo_Current); // O2_Current 배열에 대한 뮤텍스
	//		if (PlayerCharacter->GetProtocolLibrary()->CO_Current.Num() > 0) {
	//			density = PlayerCharacter->GetProtocolLibrary()->CO_Current[0];
	//			PlayerCharacter->GetProtocolLibrary()->CO_Current.RemoveAt(0);
	//		}
	//		else {
	//			//UE_LOG(LogTemp, Error, TEXT("O2_Current array is empty"));
	//		}
	//	}
	//}
	//else if (selectedPV == CO2) {
	//	{
	//		FScopeLock Lock(&PlayerCharacter->GetProtocolLibrary()->CriticalSection);
	//		if (PlayerCharacter->GetProtocolLibrary()->Co2_Current.Num() > 0) {
	//			density = PlayerCharacter->GetProtocolLibrary()->Co2_Current[0];
	//			PlayerCharacter->GetProtocolLibrary()->Co2_Current.RemoveAt(0);
	//		}
	//		else {
	//			//UE_LOG(LogTemp, Error, TEXT("Co2_Current array is empty"));
	//		}
	//	}
	//}


	//UE_LOG(LogTemp, Error, TEXT("GetOnlyCurrentDensity %lf"), density);

	if (changeToPercent) {

		//UE_LOG(LogTemp, Log, TEXT("0 : %lf, 1 : %lf, 2 : %lf, 3 : %lf , 4 : %lf , 5 : %lf , 6 : %lf"),  AVoxel_Color::DENSITY_MIN[0], AVoxel_Color::DENSITY_MIN[1], AVoxel_Color::DENSITY_MIN[2], AVoxel_Color::DENSITY_MIN[3], AVoxel_Color::DENSITY_MIN[4], AVoxel_Color::DENSITY_MIN[5], AVoxel_Color::DENSITY_MIN[6]);

		double densityPercent = (density - AVoxel_Color::DENSITY_MIN[selectedPV]) / (AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV]) * 100;
		//UE_LOG(LogTemp, Log, TEXT("[%d]Percent Data: %lf | density: %lf"), (int32)selectedPV, densityPercent, density);
		//UE_LOG(LogTemp, Log, TEXT("selected : [%d], density: %lf, DENSITY_MIN[selectedPV] : %lf, DENSITY_MAX[selectedPV : %lf,  Percent Data: %lf "), (int32)selectedPV, density, AVoxel_Color::DENSITY_MIN[selectedPV], AVoxel_Color::DENSITY_MAX[selectedPV] , densityPercent );
		//UE_LOG(LogTemp, Log, TEXT("AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV] : [%lf], "), AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV]);
		//UE_LOG(LogTemp, Log, TEXT("density - AVoxel_Color::DENSITY_MIN[selectedPV] : [%lf], "), density - AVoxel_Color::DENSITY_MIN[selectedPV]);
		//UE_LOG(LogTemp, Log, TEXT("density : [%lf]"), densityPercent);
		if (densityPercent > 1.0f) {
			return 1.0f;
		}
		else if (densityPercent < 0.0f) {
			return 0.0f;
		}

		return densityPercent;
	}

	/* 중요) 나중에 MIn과 MAX에 대하여 Persent를 구해야함 */
	//float densityPercent;

	return density;
}


/*
	점을 찍을 때 쓰는 함수
*/

double UAllStateWidgetBFL::GetCurrentLocationOfDensity(AUnrealClientCharacter* PlayerCharacter, KindPV selectedPV, float nowTime, bool isBox, int32 index, bool changeToPercent) {
	if (PlayerCharacter == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not found the Player Character!"));
		return false;
	}
	UE_LOG(LogTemp, Error, TEXT("selectedPV : %d"), (int32)selectedPV);
	double density = 0.0f;
	//double tempDensity = 0.0f;  // 임시 변수

	//// 락 프리 큐로 자원 접근
	//if (selectedPV == CO2) {
	//	if (PlayerCharacter->GetProtocolLibrary()->CO2_LocationQueue.Dequeue(tempDensity)) {
	//		density = tempDensity;
	//	}
	//}
	//else if (selectedPV == O2) {
	//	if (PlayerCharacter->GetProtocolLibrary()->O2_LocationQueue.Dequeue(tempDensity)) {
	//		density = tempDensity;
	//	}
	//}
	//else if (selectedPV == CO) {
	//	if (PlayerCharacter->GetProtocolLibrary()->CO_LocationQueue.Dequeue(tempDensity)) {
	//		density = tempDensity;
	//	}
	//}
	//else if (selectedPV == TEMP) {
	//	if (PlayerCharacter->GetProtocolLibrary()->TEMP_LocationQueue.Dequeue(tempDensity)) {
	//		density = tempDensity;
	//	}
	//}
	//else if (selectedPV == VELOCITY) {
	//	if (PlayerCharacter->GetProtocolLibrary()->VELOCITY_LocationQueue.Dequeue(tempDensity)) {
	//		density = tempDensity;
	//	}
	//}
	//else if (selectedPV == ACCEL) {
	//	if (PlayerCharacter->GetProtocolLibrary()->ACCEL_LocationQueue.Dequeue(tempDensity)) {
	//		density = tempDensity;
	//	}
	//}
	//else if (selectedPV == FUEL) {
	//	if (PlayerCharacter->GetProtocolLibrary()->FUEL_LocationQueue.Dequeue(tempDensity)) {
	//		density = tempDensity;
	//	}
	//}


	//if (changeToPercent) {
	//	double densityPercent = (density - AVoxel_Color::DENSITY_MIN[selectedPV]) / (AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV]) * 100;
	//	UE_LOG(LogTemp, Log, TEXT("selectedPV : %d, density : [%lf]"), (int32) selectedPV, densityPercent);
	//	if (densityPercent > 1.0f) {
	//		return 1.0f;
	//	}
	//	else if (densityPercent < 0.0f) {
	//		return 0.0f;
	//	}

	//	return densityPercent;
	//}

	return density;
}

//double UAllStateWidgetBFL::GetCurrentLocationOfDensity(AUnrealClientCharacter* PlayerCharacter, KindPV selectedPV, float nowTime, bool isBox, int32 index, bool changeToPercent) {
//	if (PlayerCharacter == nullptr) {
//		UE_LOG(LogTemp, Error, TEXT("Not found the Player Character!"));
//		return false;
//	}
//	UE_LOG(LogTemp, Error, TEXT("selectedPV : %d"), (int32)selectedPV);
//	double density = 0.0f;
//
//
//	if (selectedPV == CO2) {
//		{
//			FScopeLock Lock(&PlayerCharacter->GetProtocolLibrary()->CriticalSectionCO2_Location);
//			if (PlayerCharacter->GetProtocolLibrary()->Co2_Location.Num() > 0) {
//				density = PlayerCharacter->GetProtocolLibrary()->Co2_Location[0];
//				PlayerCharacter->GetProtocolLibrary()->Co2_Location.RemoveAt(0);
//			}
//
//		}
//	}
//	else if (selectedPV == O2) {
//		{
//			FScopeLock Lock(&PlayerCharacter->GetProtocolLibrary()->CriticalSectionO2_Location);
//			if (PlayerCharacter->GetProtocolLibrary()->O2_Location.Num() > 0) {
//				density = PlayerCharacter->GetProtocolLibrary()->O2_Location[0];
//				PlayerCharacter->GetProtocolLibrary()->O2_Location.RemoveAt(0);
//			}
//		}
//	}
//
//	if (changeToPercent) {
//
//		//UE_LOG(LogTemp, Log, TEXT("0 : %lf, 1 : %lf, 2 : %lf, 3 : %lf , 4 : %lf , 5 : %lf , 6 : %lf"),  AVoxel_Color::DENSITY_MIN[0], AVoxel_Color::DENSITY_MIN[1], AVoxel_Color::DENSITY_MIN[2], AVoxel_Color::DENSITY_MIN[3], AVoxel_Color::DENSITY_MIN[4], AVoxel_Color::DENSITY_MIN[5], AVoxel_Color::DENSITY_MIN[6]);
//
//		double densityPercent = (density - AVoxel_Color::DENSITY_MIN[selectedPV]) / (AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV]) * 100;
//		//UE_LOG(LogTemp, Log, TEXT("[%d]Percent Data: %lf | density: %lf"), (int32)selectedPV, densityPercent, density);
//		//UE_LOG(LogTemp, Log, TEXT("selected : [%d], density: %lf, DENSITY_MIN[selectedPV] : %lf, DENSITY_MAX[selectedPV : %lf,  Percent Data: %lf "), (int32)selectedPV, density, AVoxel_Color::DENSITY_MIN[selectedPV], AVoxel_Color::DENSITY_MAX[selectedPV] , densityPercent );
//		//UE_LOG(LogTemp, Log, TEXT("AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV] : [%lf], "), AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV]);
//		//UE_LOG(LogTemp, Log, TEXT("density - AVoxel_Color::DENSITY_MIN[selectedPV] : [%lf], "), density - AVoxel_Color::DENSITY_MIN[selectedPV]);
//		UE_LOG(LogTemp, Log, TEXT("density : [%lf]"), densityPercent);
//		if (densityPercent > 1.0f) {
//			return 1.0f;
//		}
//		else if (densityPercent < 0.0f) {
//			return 0.0f;
//		}
//
//		return densityPercent;
//	}
//
//	/* 중요) 나중에 MIn과 MAX에 대하여 Persent를 구해야함 */
//	//float densityPercent;
//
//	return density;
//}

// -- 준상 ---

/* 
	Box를 그릴때 사용하는 함수
*/
//double UAllStateWidgetBFL::GetOnlyCurrentDensity(AUnrealClientCharacter* PlayerCharacter, KindPV selectedPV, float nowTime, bool isBox, int32 index, bool changeToPercent) {
//	if (PlayerCharacter == nullptr) {
//		UE_LOG(LogTemp, Error, TEXT("Not found the Player Character!"));
//		return false;
//	}
//	UE_LOG(LogTemp, Error, TEXT("selectedPV : %d"), (int32)selectedPV);
//	double density = 0.0f;
//	int32& ThisCnt = PlayerCharacter->GetProtocolLibrary()->LoopNowGraphCnt;
//
//	if (isBox) {
//		ThisCnt = PlayerCharacter->GetProtocolLibrary()->LoopBoxNowGraphCnt;
//	}
//
//
//	// 배열이 비어 있거나 ThisCnt가 유효하지 않으면 바로 반환
//	if (PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer.Num() == 0) {
//		UE_LOG(LogTemp, Error, TEXT("port8082ResponseAnswer is empty!"));
//		return 0.0f;
//	}
//	if (PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer.Num() < ThisCnt || ThisCnt < 0) {
//		UE_LOG(LogTemp, Error, TEXT("Is not corrected CurrentNowIndex!"));
//		return 0.0f;
//	}
//
//
//	if (PlayerCharacter->GetProtocolLibrary()->PredictTime == 0) {
//
//		/*	if (PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer.Num() < ThisCnt || ThisCnt < 0) {
//				UE_LOG(LogTemp, Error, TEXT("Is not corrected CurrentNowIndex!"));
//				return 0.0f;
//			}*/
//
//		if (!PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer.IsEmpty()) {
//			FScopeLock Lock(&PlayerCharacter->GetProtocolLibrary()->CriticalSection);  // CriticalSection으로 배열 접근 동기화
//			density = PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer[ThisCnt];
//			//UE_LOG(LogTemp, Error, TEXT("GetCurrentLocationOfDensity %lf") , density);
//		}
//	}
//
//	UE_LOG(LogTemp, Log, TEXT("Counted Count: ----> %d | port8082ResponseAnswer.Num(): %d "), ThisCnt, PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer.Num());
//	if (ThisCnt >= PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer.Num() - 1) {
//		ThisCnt = 0;
//	}
//	else {
//		ThisCnt++;
//	}
//
//	/*AProtocolLibrary::PutPortDataToOneVar<AUnrealClientCharacter::LocationStatus, float>(PlayerCharacter->CurrentLocationStatus, density, selectedPV);
//
//	density = PlayerCharacter->CurrentLocationStatus[selectedPV];*/
//
//	if (changeToPercent) {
//
//		//UE_LOG(LogTemp, Log, TEXT("0 : %lf, 1 : %lf, 2 : %lf, 3 : %lf , 4 : %lf , 5 : %lf , 6 : %lf"),  AVoxel_Color::DENSITY_MIN[0], AVoxel_Color::DENSITY_MIN[1], AVoxel_Color::DENSITY_MIN[2], AVoxel_Color::DENSITY_MIN[3], AVoxel_Color::DENSITY_MIN[4], AVoxel_Color::DENSITY_MIN[5], AVoxel_Color::DENSITY_MIN[6]);
//
//		double densityPercent = (density - AVoxel_Color::DENSITY_MIN[selectedPV]) / (AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV]) * 100;
//		//UE_LOG(LogTemp, Log, TEXT("[%d]Percent Data: %lf | density: %lf"), (int32)selectedPV, densityPercent, density);
//		//UE_LOG(LogTemp, Log, TEXT("selected : [%d], density: %lf, DENSITY_MIN[selectedPV] : %lf, DENSITY_MAX[selectedPV : %lf,  Percent Data: %lf "), (int32)selectedPV, density, AVoxel_Color::DENSITY_MIN[selectedPV], AVoxel_Color::DENSITY_MAX[selectedPV] , densityPercent );
//		//UE_LOG(LogTemp, Log, TEXT("AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV] : [%lf], "), AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV]);
//		//UE_LOG(LogTemp, Log, TEXT("density - AVoxel_Color::DENSITY_MIN[selectedPV] : [%lf], "), density - AVoxel_Color::DENSITY_MIN[selectedPV]);
//		UE_LOG(LogTemp, Log, TEXT("density : [%lf]"), densityPercent);
//		if (densityPercent > 1.0f) {
//			return 1.0f;
//		}
//		else if (densityPercent < 0.0f) {
//			return 0.0f;
//		}
//
//		return densityPercent;
//	}
//
//	/* 중요) 나중에 MIn과 MAX에 대하여 Persent를 구해야함 */
//	//float densityPercent;
//
//	return density;
//}
//
//
///*
//	점을 찍을 때 쓰는 함수
//*/
//double UAllStateWidgetBFL::GetCurrentLocationOfDensity(AUnrealClientCharacter* PlayerCharacter, KindPV selectedPV, float nowTime, bool isBox, int32 index, bool changeToPercent) {
//	if (PlayerCharacter == nullptr) {
//		UE_LOG(LogTemp, Error, TEXT("Not found the Player Character!"));
//		return false;
//	}
//	UE_LOG(LogTemp, Error, TEXT("selectedPV : %d"), (int32) selectedPV);
//	double density = 0.0f;
//	int32& ThisCnt = PlayerCharacter->GetProtocolLibrary()->LoopNowGraphCnt;
//
//	if (isBox) {
//		ThisCnt = PlayerCharacter->GetProtocolLibrary()->LoopBoxNowGraphCnt;
//	}
//
//
//	// 배열이 비어 있거나 ThisCnt가 유효하지 않으면 바로 반환
//	if (PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer.Num() == 0) {
//		UE_LOG(LogTemp, Error, TEXT("port8082ResponseAnswer is empty!"));
//		return 0.0f;
//	}
//	if (PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer.Num() < ThisCnt || ThisCnt < 0) {
//		UE_LOG(LogTemp, Error, TEXT("Is not corrected CurrentNowIndex!"));
//		return 0.0f;
//	}
//
//
//	if (PlayerCharacter->GetProtocolLibrary()->PredictTime == 0) {
//
//	/*	if (PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer.Num() < ThisCnt || ThisCnt < 0) {
//			UE_LOG(LogTemp, Error, TEXT("Is not corrected CurrentNowIndex!"));
//			return 0.0f;
//		}*/
//
//		if (!PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer.IsEmpty()) {
//			FScopeLock Lock(&PlayerCharacter->GetProtocolLibrary()->CriticalSection);  // CriticalSection으로 배열 접근 동기화
//			density = PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer[ThisCnt];
//			//UE_LOG(LogTemp, Error, TEXT("GetCurrentLocationOfDensity %lf") , density);
//		}
//	}
//
//	UE_LOG(LogTemp, Log, TEXT("Counted Count: ----> %d | port8082ResponseAnswer.Num(): %d "), ThisCnt, PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer.Num());
//	if (ThisCnt >= PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswer.Num()-1) {
//		ThisCnt = 0;
//	}
//	else {
//		ThisCnt++;
//	}
//
//	/*AProtocolLibrary::PutPortDataToOneVar<AUnrealClientCharacter::LocationStatus, float>(PlayerCharacter->CurrentLocationStatus, density, selectedPV);
//
//	density = PlayerCharacter->CurrentLocationStatus[selectedPV];*/
//	
//	if (changeToPercent) {
//
//		//UE_LOG(LogTemp, Log, TEXT("0 : %lf, 1 : %lf, 2 : %lf, 3 : %lf , 4 : %lf , 5 : %lf , 6 : %lf"),  AVoxel_Color::DENSITY_MIN[0], AVoxel_Color::DENSITY_MIN[1], AVoxel_Color::DENSITY_MIN[2], AVoxel_Color::DENSITY_MIN[3], AVoxel_Color::DENSITY_MIN[4], AVoxel_Color::DENSITY_MIN[5], AVoxel_Color::DENSITY_MIN[6]);
//
//		double densityPercent = (density - AVoxel_Color::DENSITY_MIN[selectedPV]) / (AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV]) * 100;
//		//UE_LOG(LogTemp, Log, TEXT("[%d]Percent Data: %lf | density: %lf"), (int32)selectedPV, densityPercent, density);
//		//UE_LOG(LogTemp, Log, TEXT("selected : [%d], density: %lf, DENSITY_MIN[selectedPV] : %lf, DENSITY_MAX[selectedPV : %lf,  Percent Data: %lf "), (int32)selectedPV, density, AVoxel_Color::DENSITY_MIN[selectedPV], AVoxel_Color::DENSITY_MAX[selectedPV] , densityPercent );
//		//UE_LOG(LogTemp, Log, TEXT("AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV] : [%lf], "), AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV]);
//		//UE_LOG(LogTemp, Log, TEXT("density - AVoxel_Color::DENSITY_MIN[selectedPV] : [%lf], "), density - AVoxel_Color::DENSITY_MIN[selectedPV]);
//		UE_LOG(LogTemp, Log, TEXT("density : [%lf]"), densityPercent);
//		if (densityPercent > 1.0f) {
//			return 1.0f;
//		}
//		else if (densityPercent < 0.0f) {
//			return 0.0f;
//		}
//		
//		return densityPercent;
//	}
//
//	/* 중요) 나중에 MIn과 MAX에 대하여 Persent를 구해야함 */
//	//float densityPercent;
//
//	return density;
//}

FVector2D UAllStateWidgetBFL::GetCurrentScreenPointCoordinate(FName SeriesId, UWidget* KantanWidget) {
	TArray<FVector2D> DrawPoints;

	//GetLinePointsToDraw();

	return FVector2D();
}

FVector2D UAllStateWidgetBFL::GetThisScreenPointCoordinate(UWidget* KantanWidget, FVector2D ThisCoordinate, double RangeOfAxisX, double RangeOfAxisY, bool isFuture) {
	const double UNIT_ERROR_RATE_OF_X = 0.10f; // 비율에 따른 x좌표 값 오차율 지정, Y는 괜찮지만 X가 문제임 (보통 n배당 (n-1)*0.25)씩 차이가 난다.

	if (KantanWidget == nullptr) {
		return FVector2D(-99.0f, -99.0f);
	}
	
	FGeometry WidgetGeometry = KantanWidget->GetCachedGeometry();

	double graphOriginX = WidgetGeometry.Position.X;
	double graphOriginY = WidgetGeometry.GetLocalSize().Y;
	
	double graphGridLineLengthX = ((WidgetGeometry.GetLocalSize().X - WidgetGeometry.Position.X) / RangeOfAxisX);
	double graphGridLineLengthY = ((WidgetGeometry.Position.Y - WidgetGeometry.GetLocalSize().Y) / RangeOfAxisY);
	
	if (ThisCoordinate.X > RangeOfAxisX) {
		ThisCoordinate.X = RangeOfAxisX;
		//UE_LOG(LogTemp, Log, TEXT("-----> [Position], [GetLocalSize] : [%lf, %lf], [%lf, %lf]"), WidgetGeometry.Position.X, WidgetGeometry.Position.Y, WidgetGeometry.GetLocalSize().X, WidgetGeometry.GetLocalSize().Y);
	}

	if (isFuture) {
		graphGridLineLengthX = (((WidgetGeometry.GetLocalSize().X* 2.6) - WidgetGeometry.Position.X) / RangeOfAxisX);
	}

	FVector2D ScreenSize;
	GEngine->GameViewport->GetViewportSize(ScreenSize);
	double errorRateOfX = 0.0f;

	if (ScreenSize.X > ScreenSize.Y) {
		errorRateOfX = graphGridLineLengthX *((ScreenSize.X / ScreenSize.Y) * UNIT_ERROR_RATE_OF_X);
	}

	//UE_LOG(LogTemp, Log, TEXT("Position: (%lf, %lf) "), WidgetGeometry.Position.X, WidgetGeometry.Position.Y)
	//UE_LOG(LogTemp, Log, TEXT("GetLocalSize: (%lf, %lf) "), WidgetGeometry.GetLocalSize().X, WidgetGeometry.GetLocalSize().Y)
	return FVector2D((graphOriginX + (graphGridLineLengthX * ThisCoordinate.X) + errorRateOfX ), (graphOriginY + (graphGridLineLengthY * ThisCoordinate.Y)));
}

/* 
['박스'하나 그릴때 쓰는 Future Density]
*/
double UAllStateWidgetBFL::GetOnlyFutureLocationOfDensity(int32 FutureTime, AUnrealClientCharacter* PlayerCharacter, KindPV SelectedPV, bool changeToPercent) {
	int32& ThisCnt = PlayerCharacter->GetProtocolLibrary()->LoopBoxNowGraphCnt;
	double density = 0.0f;


	// <--------------------- 예외검사 Start --------------------->
	if (PlayerCharacter == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not found the Player Character!"));
		return 0.0f;
	}

	// 배열이 비어 있거나 ThisCnt가 유효하지 않으면 바로 반환
	if (PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswerFutureOfDensity.Num() == 0) {
		UE_LOG(LogTemp, Error, TEXT("port8082ResponseAnswer is empty!"));
		return 0.0f;
	}
	if (PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswerFutureOfDensity.Num() < ThisCnt || ThisCnt < 0) {
		UE_LOG(LogTemp, Error, TEXT("Is not corrected CurrentNowIndex!"));
		return 0.0f;
	}
	// <--------------------- 예외검사 End --------------------->

	if (!PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswerFutureOfDensity.IsEmpty()) {

		density = PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswerFutureOfDensity[ThisCnt];
		UE_LOG(LogTemp, Error, TEXT("GetCurrentLocationOfDensity %lf"), density);
	}
	

	if (ThisCnt >= PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswerFutureOfDensity.Num() - 1) {
		ThisCnt = 0;
	}
	else {
		ThisCnt++;
	}

	if (changeToPercent) {

		//UE_LOG(LogTemp, Log, TEXT("0 : %lf, 1 : %lf, 2 : %lf, 3 : %lf , 4 : %lf , 5 : %lf , 6 : %lf"),  AVoxel_Color::DENSITY_MIN[0], AVoxel_Color::DENSITY_MIN[1], AVoxel_Color::DENSITY_MIN[2], AVoxel_Color::DENSITY_MIN[3], AVoxel_Color::DENSITY_MIN[4], AVoxel_Color::DENSITY_MIN[5], AVoxel_Color::DENSITY_MIN[6]);

		double densityPercent = (density - AVoxel_Color::DENSITY_MIN[SelectedPV]) / (AVoxel_Color::DENSITY_MAX[SelectedPV] - AVoxel_Color::DENSITY_MIN[SelectedPV]) * 100;
		//UE_LOG(LogTemp, Log, TEXT("[%d]Percent Data: %lf | density: %lf"), (int32)selectedPV, densityPercent, density);
		//UE_LOG(LogTemp, Log, TEXT("selected : [%d], density: %lf, DENSITY_MIN[selectedPV] : %lf, DENSITY_MAX[selectedPV : %lf,  Percent Data: %lf "), (int32)selectedPV, density, AVoxel_Color::DENSITY_MIN[selectedPV], AVoxel_Color::DENSITY_MAX[selectedPV] , densityPercent );
		//UE_LOG(LogTemp, Log, TEXT("AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV] : [%lf], "), AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV]);
		//UE_LOG(LogTemp, Log, TEXT("density - AVoxel_Color::DENSITY_MIN[selectedPV] : [%lf], "), density - AVoxel_Color::DENSITY_MIN[selectedPV]);
		UE_LOG(LogTemp, Log, TEXT("density : [%lf]"), densityPercent);
		if (densityPercent > 1.0f) {
			return 1.0f;
		}
		else if (densityPercent < 0.0f) {
			return 0.0f;
		}

		return densityPercent;
	}

	return density;
	//return FMath::RandRange(0.5f, 1.0f);
}

/* 
['점' 하나 그릴때 쓰는 Future Density] 
*/
double UAllStateWidgetBFL::GetFutureLocationOfDensity(int32 FutureTime, AUnrealClientCharacter * PlayerCharacter, KindPV SelectedPV, bool changeToPercent) {
	// 받는 것 연결해야함
	// futureTime은 궂이 안필요할수도 있음

	int32& ThisCnt = PlayerCharacter->GetProtocolLibrary()->LoopFutureGraphCnt;
	double density = 0.0f;

	 // <--------------------- 예외검사 Start --------------------->
	if (PlayerCharacter == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not found the Player Character!"));
		return false;
	}

	// 배열이 비어 있거나 ThisCnt가 유효하지 않으면 바로 반환
	if (PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswerFutureOfDensity.Num() == 0) {
		UE_LOG(LogTemp, Error, TEXT("port8082ResponseAnswer is empty!"));
		return 0.0f;
	}
	if (PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswerFutureOfDensity.Num() < ThisCnt || ThisCnt < 0) {
		UE_LOG(LogTemp, Error, TEXT("Is not corrected CurrentNowIndex!"));
		return 0.0f;
	}
	// <--------------------- 예외검사 End --------------------->

	if (!PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswerFutureOfDensity.IsEmpty()) {

		density = PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswerFutureOfDensity[ThisCnt];
		UE_LOG(LogTemp, Error, TEXT("GetCurrentLocationOfDensity %lf"), density);
	}
	

	if (ThisCnt >= PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswerFutureOfDensity.Num() - 1) {
		ThisCnt = 0;
	}
	else {
		ThisCnt++;
	}

	if (changeToPercent) {

		//UE_LOG(LogTemp, Log, TEXT("0 : %lf, 1 : %lf, 2 : %lf, 3 : %lf , 4 : %lf , 5 : %lf , 6 : %lf"),  AVoxel_Color::DENSITY_MIN[0], AVoxel_Color::DENSITY_MIN[1], AVoxel_Color::DENSITY_MIN[2], AVoxel_Color::DENSITY_MIN[3], AVoxel_Color::DENSITY_MIN[4], AVoxel_Color::DENSITY_MIN[5], AVoxel_Color::DENSITY_MIN[6]);

		double densityPercent = (density - AVoxel_Color::DENSITY_MIN[SelectedPV]) / (AVoxel_Color::DENSITY_MAX[SelectedPV] - AVoxel_Color::DENSITY_MIN[SelectedPV]) * 100;
		//UE_LOG(LogTemp, Log, TEXT("[%d]Percent Data: %lf | density: %lf"), (int32)selectedPV, densityPercent, density);
		//UE_LOG(LogTemp, Log, TEXT("selected : [%d], density: %lf, DENSITY_MIN[selectedPV] : %lf, DENSITY_MAX[selectedPV : %lf,  Percent Data: %lf "), (int32)selectedPV, density, AVoxel_Color::DENSITY_MIN[selectedPV], AVoxel_Color::DENSITY_MAX[selectedPV] , densityPercent );
		//UE_LOG(LogTemp, Log, TEXT("AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV] : [%lf], "), AVoxel_Color::DENSITY_MAX[selectedPV] - AVoxel_Color::DENSITY_MIN[selectedPV]);
		//UE_LOG(LogTemp, Log, TEXT("density - AVoxel_Color::DENSITY_MIN[selectedPV] : [%lf], "), density - AVoxel_Color::DENSITY_MIN[selectedPV]);
		UE_LOG(LogTemp, Log, TEXT("density : [%lf]"), densityPercent);
		if (densityPercent > 1.0f) {
			return 1.0f;
		}
		else if (densityPercent < 0.0f) {
			return 0.0f;
		}
		
		return densityPercent;
	}
	
	return density;
}

// PointNum: 현재 시간의 점부터 미래시간의 점까지의 갯수(화면에 보이는 점 +1 라고 보면 됨)
/* 
[점 여러개 찍는 Future Density 함수
]*/
TArray<float> UAllStateWidgetBFL::GetFutureLocationOfDensities(int32 PointNum, KindPV SelectedPV, AUnrealClientCharacter* PlayerCharacter, bool changeToPercent) {
	TArray<float> FutureDensities;
	FutureDensities.SetNum(PointNum);
	FutureDensities.Init(PointNum, 0.0f);

	int32& ThisCnt = PlayerCharacter->GetProtocolLibrary()->LoopFutureGraphCnt;

	// <--------------------- 예외검사 Start --------------------->
	if (PlayerCharacter == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not found the Player Character!"));
		return FutureDensities;
	}

	// 배열이 비어 있거나 ThisCnt가 유효하지 않으면 바로 반환
	if (PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswerFutureOfDensities.Num() == 0) {
		UE_LOG(LogTemp, Error, TEXT("port8082ResponseAnswer is empty!"));
		return FutureDensities;
	}
	if (PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswerFutureOfDensities.Num() < ThisCnt || ThisCnt < 0) {
		UE_LOG(LogTemp, Error, TEXT("Is not corrected CurrentNowIndex!"));
		return FutureDensities;
	}

	if (PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswerFutureOfDensities[ThisCnt].Num() > 6) {
		UE_LOG(LogTemp, Error, TEXT("Received invalid index of port8082ResponseAnswerFutureOfDensities"));
		return FutureDensities;
	}

	// <--------------------- 예외검사 End --------------------->

	if (!PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswerFutureOfDensities.IsEmpty()) {
		// 여러개의 미래 점은 1개 ~ 6개(max)가 될 수 있다.
		TArray<double>& ArrayData = PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswerFutureOfDensities[ThisCnt];

		if (changeToPercent) {
			double densityPercent =0.0f;
			int ArrayIndex;
			for (int i = (6 - PointNum); i < ArrayData.Num(); i++) {
				ArrayIndex = (6 - PointNum) + i;  // 시작 인덱스 조정
				if (ArrayIndex >= ArrayData.Num()) {
					break;  // 안전을 위해 배열 범위를 넘지 않도록 체크
				}

				densityPercent = (ArrayData[ArrayIndex] - AVoxel_Color::DENSITY_MIN[SelectedPV]) /
					(AVoxel_Color::DENSITY_MAX[SelectedPV] - AVoxel_Color::DENSITY_MIN[SelectedPV]) * 100;

				if (densityPercent > 1.0f || densityPercent < 0.0f) {
					return FutureDensities;
				}
				FutureDensities[i] = densityPercent;
			}
		}
		else {
			int ArrayIndex;
			for (int i = (6 - PointNum); i < ArrayData.Num(); i++) {
				ArrayIndex = (6 - PointNum) + i;  // 시작 인덱스 조정
				if (ArrayIndex >= ArrayData.Num()) {
					break;  // 안전을 위해 배열 범위를 넘지 않도록 체크
				}
				FutureDensities[i] = ArrayData[ArrayIndex];
			}
		}
	}
	

	if (ThisCnt >= PlayerCharacter->GetProtocolLibrary()->port8082ResponseAnswerFutureOfDensities.Num() - 1) {
		ThisCnt = 0;
	}
	else {
		ThisCnt++;
	}
	return FutureDensities;
}

// 다음번에 loop가 돌때 Data를 받기 위해 설정
void UAllStateWidgetBFL::RequestFutureGrpahData(int32 FutureTime, AUnrealClientCharacter* PlayerCharacter) {
	PlayerCharacter->GetProtocolLibrary()->FutureTimeAlpha = FutureTime;
	// 다음번 loop에서 미래값을 가져오라고 요청함

}

void UAllStateWidgetBFL::ResetGraphIndexs(AUnrealClientCharacter* PlayerCharacter)
{
	PlayerCharacter->GetProtocolLibrary()->LoopNowGraphCnt = 0;
	PlayerCharacter->GetProtocolLibrary()->LoopBoxNowGraphCnt = 0;
	PlayerCharacter->GetProtocolLibrary()->LoopFutureGraphCnt = 0;
	PlayerCharacter->GetProtocolLibrary()->LoopBoxFutureGraphCnt = 0;
}
