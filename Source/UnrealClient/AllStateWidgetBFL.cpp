// Fill out your copyright notice in the Description page of Project Settings.


#include "AllStateWidgetBFL.h"
#include "Engine/World.h"
#include "Engine/Engine.h"

double UAllStateWidgetBFL::StartTime;
double UAllStateWidgetBFL::changeTime;


void UAllStateWidgetBFL::SetNowPVData(UObject* WorldContextObject, KindPV selectedPV) {

	if (!WorldContextObject) return;

	UWorld* World = WorldContextObject->GetWorld();
	if (!World) return;

	AProtocolLibrary* ProtocolLibraryInstance = AProtocolLibrary::GetInstance(World);

	UE_LOG(LogTemp, Log, TEXT("----------------------> SetNowData Opened!!! [%d]"), (int32)selectedPV);

	if (selectedPV == CO2) {
		ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.CO2);
	}
	else if (selectedPV == O2) {
		ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.O2);
	}
	else if (selectedPV == CO)
	{
		ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.CO);
	}
	else if (selectedPV == TEMP)
	{
		ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.TEMP);

	}
	else if (selectedPV == VELOCITY)
	{
		ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.VELOCITY);

	}
	else if (selectedPV == ACCEL)
	{
		ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.ACCEL);
	}
	else if (selectedPV == FUEL)
	{
		ProtocolLibraryInstance->port8081Request.SetOnlyOneTrue(ProtocolLibraryInstance->port8081Request.FUEL);
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
		// Image ������ Brush Tint Color�� ����
		Image->SetColorAndOpacity(NewColor);
	}
}

void UAllStateWidgetBFL::SetImagesColor(const TArray<UImage*>& Images)
{
	FLinearColor RedColor = FLinearColor::Red;  // ������ ����

	// �迭�� �ִ� ��� Image ������ ������ ���������� ����
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



	// ���� �ð��� �� ������ ���, changeTime�� ����
	double CurrentTimeInSeconds = FPlatformTime::Seconds() - StartTime + changeTime;

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


void UAllStateWidgetBFL::RequestGraphData(AUnrealClientCharacter* PlayerCharacter, float nowTime) {
	/*
		nowTime�� ������� ������ ��û�ϰ�, ���� �޾Ҵٰ� ������
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

	// (TEST) �ۼ��� �޼���
	Message.Append("KI");
	Message.Append(Instance->port8082Request.CO2 ? TEXT("1") : TEXT("0"));
	Message.Append(Instance->port8082Request.O2 ? TEXT("1") : TEXT("0"));
	Message.Append(Instance->port8082Request.CO ? TEXT("1") : TEXT("0"));
	Message.Append(Instance->port8082Request.TEMP ? TEXT("1") : TEXT("0"));
	Message.Append(Instance->port8082Request.VELOCITY ? TEXT("1") : TEXT("0"));
	Message.Append(Instance->port8082Request.ACCEL ? TEXT("1") : TEXT("0"));
	Message.Append(Instance->port8082Request.FUEL ? TEXT("1") : TEXT("0"));

	// (TEST) ���� ���� ���� value ä���
	PlayerCharacter->CurrentLocationStatus.CO2 = (Instance->port8082Request.CO2) ? FMath::RandRange(0.5f, 1.0f) : 0.0f;
	PlayerCharacter->CurrentLocationStatus.O2 = Instance->port8082Request.O2 ? FMath::RandRange(0.5f, 1.0f) : 0.0f;
	PlayerCharacter->CurrentLocationStatus.CO = Instance->port8082Request.CO ? FMath::RandRange(0.5f, 1.0f) : 0.0f;
	PlayerCharacter->CurrentLocationStatus.TEMP = Instance->port8082Request.TEMP ? FMath::RandRange(0.5f, 1.0f) : 0.0f;
	PlayerCharacter->CurrentLocationStatus.VELOCITY = Instance->port8082Request.VELOCITY ? FMath::RandRange(0.5f, 1.0f) : 0.0f;
	PlayerCharacter->CurrentLocationStatus.ACCEL = Instance->port8082Request.ACCEL ? FMath::RandRange(0.5f, 1.0f) : 0.0f;
	PlayerCharacter->CurrentLocationStatus.FUEL = Instance->port8082Request.FUEL ? FMath::RandRange(0.5f, 1.0f) : 0.0f;

}

bool UAllStateWidgetBFL::IsSubscribe(AUnrealClientCharacter* PlayerCharacter, KindPV selectedPV) {
	FString Message = TEXT("");
	if (PlayerCharacter == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not found the Player Character!"));
		return false;
	}

	AProtocolLibrary* Instance = PlayerCharacter->GetProtocolLibrary();
	if (Instance == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not exist the character's ProtocolLibraryInstance!"));
		return false;
	}

	bool isSubscribe = false;

	//AProtocolLibrary::PutPortDataToOneVar<AProtocolLibrary::Port8082_request, bool>(Instance->port8082Request, isSubscribe, selectedPV);

	switch (selectedPV) {
	case CO2:
		isSubscribe = Instance->port8082Request.CO2;
		break;

	case O2:
		isSubscribe = Instance->port8082Request.O2;
		break;

	case CO:
		isSubscribe = Instance->port8082Request.CO;
		break;

	case TEMP:
		isSubscribe = Instance->port8082Request.TEMP;
		break;

	case VELOCITY:
		isSubscribe = Instance->port8082Request.VELOCITY;
		break;

	case ACCEL:
		isSubscribe = Instance->port8082Request.ACCEL;
		break;

	case FUEL:
		isSubscribe = Instance->port8082Request.FUEL;
		break;

	default:
		UE_LOG(LogTemp, Error, TEXT("Dose not exist the KindPV!!"));
		break;
	}

	return isSubscribe;
}

float UAllStateWidgetBFL::GetCurrentLocationOfDensity(AUnrealClientCharacter* PlayerCharacter, KindPV selectedPV, float nowTime, bool changeToPercent) {
	if (PlayerCharacter == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("Not found the Player Character!"));
		return false;
	}

	float density = 0.0f;
	//AProtocolLibrary::PutPortDataToOneVar<AUnrealClientCharacter::LocationStatus, float>(PlayerCharacter->CurrentLocationStatus, density, selectedPV);

	switch (selectedPV) {
	case CO2:
		density = PlayerCharacter->CurrentLocationStatus.CO2;
		break;

	case O2:
		density = PlayerCharacter->CurrentLocationStatus.O2;
		break;

	case CO:
		density = PlayerCharacter->CurrentLocationStatus.CO;
		break;

	case TEMP:
		density = PlayerCharacter->CurrentLocationStatus.TEMP;
		break;

	case VELOCITY:
		density = PlayerCharacter->CurrentLocationStatus.VELOCITY;
		break;

	case ACCEL:
		density = PlayerCharacter->CurrentLocationStatus.ACCEL;
		break;

	case FUEL:
		density = PlayerCharacter->CurrentLocationStatus.FUEL;
		break;

	default:
		UE_LOG(LogTemp, Error, TEXT("Dose not exist the KindPV!!"));
		break;
	}
	
	if (changeToPercent) {

	}

	/* �߿�) ���߿� MIn�� MAX�� ���Ͽ� Persent�� ���ؾ��� */
	//float densityPercent;

	return density;
}

FVector2D UAllStateWidgetBFL::GetCurrentScreenPointCoordinate(FName SeriesId, UWidget* KantanWidget) {
	TArray<FVector2D> DrawPoints;

	//GetLinePointsToDraw();

	return FVector2D();
}

FVector2D UAllStateWidgetBFL::GetThisScreenPointCoordinate(UWidget* KantanWidget, FVector2D ThisCoordinate, double RangeOfAxisX, double RangeOfAxisY, bool isFuture) {
	const double UNIT_ERROR_RATE_OF_X = 0.10f; // ������ ���� x��ǥ �� ������ ����, Y�� �������� X�� ������ (���� n��� (n-1)*0.25)�� ���̰� ����.

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

	return FVector2D((graphOriginX + (graphGridLineLengthX * ThisCoordinate.X) + errorRateOfX ), (graphOriginY + (graphGridLineLengthY * ThisCoordinate.Y)));
}

// PointNum: ���� �ð��� ������ �̷��ð��� �������� ����(ȭ�鿡 ���̴� �� +1 ��� ���� ��)
TArray<float> UAllStateWidgetBFL::GetFutureLocationOfDensities(int32 PointNum, KindPV SelectedPV, AUnrealClientCharacter* PlayerCharacter, bool changeToPercent){
	
	// startTime ~ endTime�� ���ؼ�
	// startTime + rangeIntergal ���� ���� �ż��� �����õ�
	//float rangeInterval = (endTime - startTime) / PointNum;
	
	// ���߿� �ٲ������
	TArray<float> Data;
	Data.SetNum(PointNum);

	

	// startTime ~ endTime����

	// ���߿� Percent�� ��ȯ�ؾ���
	if (changeToPercent) {
		for (int32 i = 0; i < PointNum; ++i) {
			Data[i] = FMath::RandRange(0.5f, 1.0f); // �迭�� �� ��ҿ� �� �Ҵ�
		}
	}

	// ����� �α� �߰�
	//UE_LOG(LogTemp, Warning, TEXT("GetFutureLocationOfDensity: Array Length = %d"), Data.Num());
	
	return Data;
}


float UAllStateWidgetBFL::GetFutureLocationOfDensity(int32 FutureTime, AUnrealClientCharacter * PlayerCharacter, KindPV SelectedPV, bool changeToPercent) {
	// �޴� �� �����ؾ���
	// futureTime�� ���� ���ʿ��Ҽ��� ����	
	
	return FMath::RandRange(0.5f, 1.0f);
}

// �������� loop�� ���� Data�� �ޱ� ���� ����
void UAllStateWidgetBFL::RequestFutureGrpahData(int32 FutureTime, AUnrealClientCharacter* PlayerCharacter) {
	PlayerCharacter->GetProtocolLibrary()->FutureTimeAlpha = FutureTime;
	// ������ loop���� �̷����� ��������� ��û��

}