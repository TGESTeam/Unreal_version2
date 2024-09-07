// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtocolLibrary.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/DateTime.h" //Time 
#include "HAL/PlatformProcess.h" // For FPlatformProcess::Sleep


AProtocolLibrary* AProtocolLibrary::Instance = nullptr;
int32 ActualBufferSize = 0; // 초기값 설정

// Sets default values
AProtocolLibrary::AProtocolLibrary()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Socket8081 = nullptr;
	Socket8082 = nullptr;
	Socket8083 = nullptr;
	TimeSinceLastSend = 0.0f;

	// 각 포트를 초기화
	Port8081 = 8081;
	Port8082 = 8082;
	Port8083 = 8083;

	Port8081_request.Init(false, 7); // 7개의 false 값으로 배열 초기화
	this->SelectedValue = Port8081_request.Num();
	Port8083_request.Init(false, 3);
	Port8082_request.Init(false, 7);

	UpdateCounter = 0;
	//AnswerSizeReachedEvent = FPlatformProcess::CreateSynchEvent(false); // 자동 리셋 이벤트 생성
}

// 싱글톤 인스턴스를 반환하는 함수
AProtocolLibrary* AProtocolLibrary::GetInstance(UWorld* World)
{
	if (Instance == nullptr)
	{
		Instance = World->SpawnActor<AProtocolLibrary>(AProtocolLibrary::StaticClass());
	}
	return Instance;
}

// 싱글톤 인스턴스를 명시적으로 해제하는 함수
void AProtocolLibrary::DestroyInstance()
{
	if (Instance != nullptr)
	{
		Instance->Destroy();
		Instance = nullptr;
	}
}

AProtocolLibrary::~AProtocolLibrary()
{

	//if (AnswerSizeReachedEvent)
	//{
	//	FPlatformProcess::ReturnSynchEventToPool(AnswerSizeReachedEvent);
	//	AnswerSizeReachedEvent = nullptr;
	//}
}

// Called when the game starts or when spawned
void AProtocolLibrary::BeginPlay()
{
	Super::BeginPlay();

	// 세 개의 서버에 연결
	ConnectToServer(Socket8081, TEXT("127.0.0.1"), 8081);
	ConnectToServer(Socket8082, TEXT("127.0.0.1"), 8082);
	ConnectToServer(Socket8083, TEXT("127.0.0.1"), 8083);

	////// 서버가 준비되었는지 확인
	if ((Socket8081 && Socket8081->GetConnectionState() == SCS_Connected) && \
		(Socket8082 && Socket8082->GetConnectionState() == SCS_Connected) && \
		(Socket8083 && Socket8083->GetConnectionState() == SCS_Connected))
	{
		// 최대 버퍼 크기를 찾기 위한 초기값과 증분 설정
		int32 DesiredBufferSize = 1024 * 1024; // 1MB부터 시작
		int32 IncrementSize = 1024 * 1024; // 1MB씩 증가

		// 최대 버퍼 크기를 찾는 루프
		while (true)
		{
			int32 PreviousBufferSize = ActualBufferSize;
			Socket8081->SetReceiveBufferSize(DesiredBufferSize, ActualBufferSize);

			// 설정된 버퍼 크기가 이전과 동일하면 최대 크기에 도달한 것으로 간주
			if (ActualBufferSize == PreviousBufferSize)
			{
				break;
			}

			// 다음 시도 크기 증가
			DesiredBufferSize += IncrementSize;

			// 안전 장치: 너무 큰 값을 시도하지 않도록 제한 (예: 64MB)
			if (DesiredBufferSize > 16 * 1024 * 1024)
			{
				break;
			}
		}

		//UE_LOG(LogTemp, Log, TEXT("Attempted to set receive buffer size to: %d"), BufferSize);
		UE_LOG(LogTemp, Log, TEXT("Actual receive buffer size set to2: %d"), ActualBufferSize);
		UE_LOG(LogTemp, Log, TEXT("Socket is connected and ready to send data."));
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Socket is not connected or ready."));
	}
}

// Called every frame
void AProtocolLibrary::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	TimeSinceLastSend += DeltaTime;

	// 2초마다 메시지 전송
	if (TimeSinceLastSend >= 0.5f)
	{
		//SendMessageToServer(Socket8081, TEXT("Message to Server 1"));
		//SendMessageToServer(Socket8082, TEXT("Message to Server 2"));
		//SendMessageToServer(Socket8083, TEXT("Message to Server 3"));

		SendMessageToServer(Socket8081, 8081);
		SendMessageToServer(Socket8082, 8082);
		SendMessageToServer(Socket8083, 8083);


		TimeSinceLastSend = 0.0f;
	}
}

void AProtocolLibrary::ConnectToServer(FSocket*& Socket, const FString& ServerAddress, int32 Port)
{
	FIPv4Address IP;
	FIPv4Address::Parse(ServerAddress, IP);

	TSharedRef<FInternetAddr> Addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	Addr->SetIp(IP.Value);
	Addr->SetPort(Port);

	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	if (!Socket->Connect(*Addr))
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to connect to server %s:%d"), *ServerAddress, Port);
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("Connected to server %s:%d"), *ServerAddress, Port);
	}
}

void AProtocolLibrary::setPort8081_requestPV(int32 index, KindPV seletedPV) {

	Port8081_request[index] = true;
	this->SelectedValue = (int32)seletedPV;
	//UE_LOG(LogTemp, Log, TEXT("----------------------> setPort8081_requestPV  [%d]"), index);
}

void AProtocolLibrary::setPort8081_requestPVAllFalse() {
	Port8081_request.Init(false, 7);
}

void AProtocolLibrary::ParshingResponsePort8081(FString& ReceivedMessage)
{	// "PV" 제거
	ReceivedMessage.RemoveFromStart(TEXT("PV"));

	TArray<FString> stringArray;
	ReceivedMessage.ParseIntoArray(stringArray, TEXT(","), true);

	if (port8081ResponseAnswer.Num() > 0) // 배열에 요소가 있는지 확인
	{
		port8081ResponseAnswer.Empty(); // 모든 요소 삭제
	}
	for (const FString& str : stringArray)
	{
		double value = FCString::Atod(*str);
		this->port8081ResponseAnswer.Add(value);
	}
}
void AProtocolLibrary::ParshingResponsePort8083(FString& ReceivedMessage)
{
	UE_LOG(LogTemp, Log, TEXT("DEBUG : ParshingResponsePort8083"));

	TArray<FString> stringArray;
	ReceivedMessage.ParseIntoArray(stringArray, TEXT(","), true);

	// 잠금을 통해 배열에 안전하게 접근합니다.
	{
		FScopeLock Lock(&Mutex);
		for (const FString& str : stringArray)
		{
			double value = FCString::Atod(*str);
			this->port8083ResponseAnswer.Add(value);
		}
	}

	// 초기화 플래그 설정
	bool bInitialized = false;

	//{
		//FScopeLock Lock(&Mutex); // port8083Answer 초기화 중에 락 사용
		if (this->port8083Answer.IsEmpty() || CompletedIterations == 0)
		{
			// port8083ResponseAnswer에서 처음 10,000개의 값을 port8083Answer로 복사
			for (int32 i = 0; i < 10000; ++i)
			{
				this->port8083Answer.Add(this->port8083ResponseAnswer[i]);
			}
			this->port8083ResponseAnswer.RemoveAt(0, 10000, false);
			bInitialized = true; 
		}
	//}

	if (bInitialized)
	{
		AsyncTask(ENamedThreads::AnyBackgroundThreadNormalTask, [this]()
		{
			UE_LOG(LogTemp, Log, TEXT("DEBUG : MonitorPort8083Answer Task Triggered"));
		});
	}
}





// ---- 최종 --- 
//void AProtocolLibrary::ParshingResponsePort8083(FString& ReceivedMessage)
//{
//	UE_LOG(LogTemp, Log, TEXT("DEBUG : ParshingResponsePort8083"));
//
//	TArray<FString> stringArray;
//	ReceivedMessage.ParseIntoArray(stringArray, TEXT(","), true);
//
//	for (const FString& str : stringArray)
//	{
//		double value = FCString::Atod(*str);
//
//		{
//			FScopeLock Lock(&Mutex); // 모든 자원 접근을 보호하기 위해 추가
//			this->port8083ResponseAnswer.Add(value);
//		}
//	}
//
//	//UE_LOG(LogTemp, Log, TEXT("DEBUG : ParshingResponsePort8083-2"));
//
//	if (this->port8083Answer.IsEmpty() && shouldTriggerEvent == true)
//	{
//		{
//			//UE_LOG(LogTemp, Log, TEXT("DEBUG : ParshingResponsePort8083-3"));
//			FScopeLock Lock2(&Mutex); // port8083Answer 초기화 중에 락 사용
//			for (int32 i = 0; i < 10000; ++i)
//			{
//				this->port8083Answer.Add(this->port8083ResponseAnswer[i]);
//				//UE_LOG(LogTemp, Log, TEXT("DEBUG : ParshingResponsePort8083-4"));
//			}
//			this->port8083ResponseAnswer.RemoveAt(0, 10000, false);
//			//UE_LOG(LogTemp, Log, TEXT("DEBUG : ParshingResponsePort8083-5"));
//		}
//	}
//}



// 이거 아님
//void AProtocolLibrary::ParshingResponsePort8083(FString& ReceivedMessage)
//{	
//	{
//		// 뮤텍스를 사용하여 자원 보호
//		FScopeLock Lock(&Mutex); // 뮤텍스를 잠금
//		UE_LOG(LogTemp, Log, TEXT("DEBUG : ParshingResponsePort8083"));
//
//		//LogTemp: NewColor: R = 1.000000, G = 0.000000, B = 0.000000, A = 1.000000
//		TArray<FString> stringArray;
//		TArray<double> temp;
//		ReceivedMessage.ParseIntoArray(stringArray, TEXT(","), true);
//
//		//if (port8083ResponseAnswer.Num() > 0) // 배열에 요소가 있는지 확인
//		//{
//		//	port8083ResponseAnswer.Empty(); // 모든 요소 삭제
//		//}
//		for (const FString& str : stringArray)
//		{
//			double value = FCString::Atod(*str);
//			//temp.Add(value);
//			this->port8083ResponseAnswer.Add(value);
//			//UE_LOG(LogTemp, Log, TEXT("port8083ResponseAnswer %lf"), value);
//		}
//		//this->port8083ResponseAnswer = temp;
//		if (this->port8083ResponseAnswer.Num() > 10000)
//		{
//			FScopeLock Lock2(&Mutex); // port8083Answer 초기화 중에 락 사용
//
//			// 처음 10,000개의 요소를 port8083Answer에 추가
//			for (int32 i = 0; i < 10000; ++i)
//			{
//				this->port8083Answer.Add(this->port8083ResponseAnswer[i]);
//			}
//
//			// port8083ResponseAnswer에서 처음 10,000개의 요소를 제거
//			this->port8083ResponseAnswer.RemoveAt(0, 10000, false);
//
//			//UE_LOG(LogTemp, Log, TEXT("Added 10,000 elements to port8083Answer and removed them from port8083ResponseAnswer"));
//		}
//
//		
//
//		//if (this->CompletedIterations == 0)
//		//{
//		//	FScopeLock Lock2(&Mutex); // port8083Answer 초기화 중에 락 사용
//		//	//this->port8083Answer = this->port8083ResponseAnswer;
//		//			// port8083ResponseAnswer의 각 요소를 port8083Answer에 추가
//		//	for (double value : this->port8083ResponseAnswer)
//		//	{
//		//		this->port8083Answer.Add(value);
//		//	}
//		//}
//
//		// port8083Answer와 port8083ResponseAnswer의 길이를 로그로 출력
//		//UE_LOG(LogTemp, Log, TEXT("Length of port8083Answer: %d"), port8083Answer.Num());
//		//UE_LOG(LogTemp, Log, TEXT("Length of port8083ResponseAnswer: %d"), port8083ResponseAnswer.Num());
//
//		//// 호출 카운터 증가
//		//UpdateCounter++;
//
//		//// 7초마다 port8083Answer 값을 업데이트 (1초마다 호출되므로 7회마다 실행)
//		//if (UpdateCounter >= 5)
//		//{
//		//	if (port8083Answer != port8083ResponseAnswer) // 값이 변경된 경우에만 업데이트
//		//	{
//		//		port8083Answer = port8083ResponseAnswer;
//		//		// 로그로 업데이트 확인
//		//		//UE_LOG(LogTemp, Log, TEXT("port8083Answer updated every 7 seconds: %s"), *FString::JoinBy(port8083Answer, TEXT(", "), [](double val) { return FString::SanitizeFloat(val); }));
//
//		//		// UI 업데이트를 위해서 색상 변경 플래그를 세팅합니다.
//
//		//	}
//
//		//	UpdateCounter = 0; // 카운터 초기화
//		//}
//
//	}
//	//this->port8083Answer = this->port8083ResponseAnswer;
//}

FLinearColor AProtocolLibrary::GetLienarColor(double& density, int32 selectedPVIndex)
{
	double densityPercent;

	// PV의 범위에 따른 dencity인지 검증
	//if ((DENSITY_MIN[nowPV] > density) || (DENSITY_MAX[nowPV] < density)) {
	//    UE_LOG(LogTemp, Warning, TEXT("Inputed invalid density's value!!"));
	//    return;
	//}
	// 표현될 색의 범위를 정한다. (|a| 는 절댓값을 의미한다.) 
	// (density - 최소) / (최대 - 최소) * 100 = (범위에 대한 %) 
	// Color의
	densityPercent = (density - AVoxel_Color::DENSITY_MIN[selectedPVIndex]) / (AVoxel_Color::DENSITY_MAX[selectedPVIndex] - AVoxel_Color::DENSITY_MIN[selectedPVIndex]) * 100;

	// PV에 따른 색상 color 색깔 범위 설정
	switch ((KindPV)selectedPVIndex) {
	case O2:
		return SetColorWhiteToRedCrossSection(densityPercent, true); // Red ~ White
		break;

	case CO2:
		return SetColorWhiteToRedCrossSection(densityPercent); // White ~ Red
		break;

	case CO:
		return SetColorWhiteToRedCrossSection(densityPercent); // White ~ Red
		break;

	case TEMP:
		return SetColorBlueToRedCrossSection(densityPercent, true); // Red ~ Blue
		break;

	case VELOCITY:
		return SetColorBlueToRedCrossSection(densityPercent); // Blue ~ Red
		break;

	case ACCEL:
		return SetColorBlueToRedCrossSection(densityPercent); // Blue ~ Red
		break;

	case FUEL:
		return SetColorWhiteToBlackCrossSection(densityPercent); // White ~ Black
		break;
	default:
		// 투명색 설정
		// 4번째 param을 0.0f로 해야함
		return FLinearColor(1.0f, 0.25f, 0.25f, 0.2f);
		break;
	}

	return FLinearColor();
}

FLinearColor AProtocolLibrary::SetColorWhiteToRedCrossSection(double& density, bool reverse)
{
	if (reverse) { // Red ~ White
		density = (1.0f - density);
	}

	return FLinearColor(1.0f, density, density, 1.0f);
}

FLinearColor AProtocolLibrary::SetColorBlueToRedCrossSection(double& density, bool reverse)
{
	if (reverse) {
		density = (1.0f - density); // densityPersent는 오직 0~1 사이 이므로 음수 판별x
	}


	if (density >= 0.0f && density <= 0.25f) { // R증가, B감소
		return FLinearColor((density / 2), 0.0f, (1.0f - (density / 2)), 1.0f);
	}
	else if ((density > 0.25f && density <= 0.4f)) { // R 2배증가, B 2배감소 (보라색을 나타내지 않기 위해)
		return FLinearColor((density * 2), 0.0f, ((1.0f - density) * 2), 1.0f);
	}
	else if (density > 0.4f) { // 위의 상태를 천천히 유지시킴
		return FLinearColor(density, 0.0f, (1.0f - density), 1.0f);
	}

	return FLinearColor();
}

FLinearColor AProtocolLibrary::SetColorWhiteToBlackCrossSection(double& density, bool reverse)
{
	if (reverse) {
		density = (1.0f - density);
	}

	return FLinearColor((1.0f - density), (1.0f - density), (1.0f - density), 1.0f);
}

void AProtocolLibrary::setPort8082_request(int32 index, KindPV seletedPV) {

	if (Port8082_request[index] == true)
	{
		Port8082_request[index] = false;
	}
	else
	{
		Port8082_request[index] = true;
	}
	//UE_LOG(LogTemp, Log, TEXT("----------------------> setPort8082_request  [%d]"), index);
}

void AProtocolLibrary::setPort8083_request(int32 index, FloorPlanPV seletedPV) {

	if (Port8083_request[index] == true)
	{
		Port8083_request[index] = false;
	}
	else
	{
		Port8083_request[index] = true;
	}
	//UE_LOG(LogTemp, Log, TEXT("----------------------> setPort8083_request  [%d]"), index);
}

void AProtocolLibrary::setPort8083_requestPVAllFalse() {

	Port8083_request.Init(false, 3);
	//UE_LOG(LogTemp, Log, TEXT("----------------------> setPort8083_request  [%d]"), index);
}

//void AProtocolLibrary::setPort8081_requestPVAllFalse() {
//	Port8081_request.Init(false, 7);
//}

void AProtocolLibrary::SendMessageToServer(FSocket* Socket, int32 Port)
{
	if (Socket && Socket->GetConnectionState() == SCS_Connected)
	{
		if (Port == 8081)
		{
			FString Message; // 	 = TEXT("Message to Server 2");
			//1.KI
			Message += "KI";

			//UE_LOG(LogTemp, Log, TEXT("CO2 Value: %s"), port8081Request.CO2 ? TEXT("true") : TEXT("false"));
			FString ValueToAdd;
			for (size_t i = 0; i < Port8081_request.Num(); i++)
			{
				ValueToAdd = Port8081_request[i] ? TEXT("1") : TEXT("0");
				Message += ValueToAdd;
			}

			//for (size_t i = 0; i < 7; i++)
			//{
			//	FString ValueToAdd = TEXT("0");

			//	// port8081Request의 각 멤버를 순차적으로 검사
			//	switch (i)
			//	{
			//		case 0: ValueToAdd = port8081Request.CO2 ? TEXT("1") : TEXT("0"); break;
			//		case 1: ValueToAdd = port8081Request.O2 ? TEXT("1") : TEXT("0"); break;
			//		case 2: ValueToAdd = port8081Request.CO ? TEXT("1") : TEXT("0"); break;
			//		case 3: ValueToAdd = port8081Request.TEMP ? TEXT("1") : TEXT("0"); break;
			//		case 4: ValueToAdd = port8081Request.VELOCITY ? TEXT("1") : TEXT("0"); break;
			//		case 5: ValueToAdd = port8081Request.ACCEL ? TEXT("1") : TEXT("0"); break;
			//		case 6: ValueToAdd = port8081Request.FUEL ? TEXT("1") : TEXT("0"); break;
			//		default: break;
			//	}
			//	Message += ValueToAdd;
			//}

			//LO
			Message += "LO";
			Message += FString::Printf(TEXT("%lf"), PlayerLocation.X) + "," \
				+ FString::Printf(TEXT("%lf"), PlayerLocation.Y) + "," \
				+ FString::Printf(TEXT("%lf"), PlayerLocation.Z);
			//TI
			Message += "TI";
			FTimespan NewTime = CurrentTime + FTimespan::FromSeconds(0.1);
			int32 Hours = NewTime.GetHours();
			int32 Minutes = NewTime.GetMinutes();
			int32 Seconds = NewTime.GetSeconds();
			int32 Milliseconds = static_cast<int32>(NewTime.GetTotalMilliseconds()) % 1000;
			FString TimeString = FString::Printf(TEXT("%02d:%02d:%02d.%03d"), Hours, Minutes, Seconds, Milliseconds);
			Message += *TimeString;

			const TCHAR* SerializedChar = *Message;
			int32 Size = FCString::Strlen(SerializedChar) + 1;
			int32 Sent = 0;

			//UE_LOG(LogTemp, Log, TEXT("Message Status: %s"), *Message);
			Socket->Send((uint8*)TCHAR_TO_UTF8(SerializedChar), Size, Sent);

			// 수신된 데이터의 크기에 맞춰 문자열 변환
			FString ReceivedMessage = ReceiveData(Socket);
			//UE_LOG(LogTemp, Log, TEXT("Port 8081 Received from server: %s"), *ReceivedMessage);

			if (ReceivedMessage.Contains(TEXT("None"))) // None일 때
			{
				if (!port8081ResponseAnswer.IsEmpty())
					port8081ResponseAnswer.Empty();
			}
			else //PV값이 있을 때
			{
				ParshingResponsePort8081(ReceivedMessage);
			}
		}
		else if (Port == 8082)
		{
			FString Message; // 	 = TEXT("Message to Server 2");
			//KI
			Message += "KI";
			FString ValueToAdd;
			for (size_t i = 0; i < Port8082_request.Num(); i++)
			{
				ValueToAdd = Port8082_request[i] ? TEXT("1") : TEXT("0");
				Message += ValueToAdd;
			}
			//for (size_t i = 0; i < 7; i++) // 중복 가능
			//{
			//	FString ValueToAdd = TEXT("0");

			//	// port8081Request의 각 멤버를 순차적으로 검사
			//	switch (i)
			//	{
			//		case 0: ValueToAdd = port8082Request.CO2 ? TEXT("1") : TEXT("0"); break;
			//		case 1: ValueToAdd = port8082Request.O2 ? TEXT("1") : TEXT("0"); break;
			//		case 2: ValueToAdd = port8082Request.CO ? TEXT("1") : TEXT("0"); break;
			//		case 3: ValueToAdd = port8082Request.TEMP ? TEXT("1") : TEXT("0"); break;
			//		case 4: ValueToAdd = port8082Request.VELOCITY ? TEXT("1") : TEXT("0"); break;
			//		case 5: ValueToAdd = port8082Request.ACCEL ? TEXT("1") : TEXT("0"); break;
			//		case 6: ValueToAdd = port8082Request.FUEL ? TEXT("1") : TEXT("0"); break;
			//		default: break;
			//	}
			//	Message += ValueToAdd;
			//}


			//LO
			Message += "LO";
			Message += FString::Printf(TEXT("%lf"), PlayerLocation.X) + "," \
				+ FString::Printf(TEXT("%lf"), PlayerLocation.Y) + "," \
				+ FString::Printf(TEXT("%lf"), PlayerLocation.Z);
			//TN
			Message += "TN";
			FTimespan GrpahNewTime = CurrentTime + FTimespan::FromSeconds((double) PredictTime);
			int32 Hours = GrpahNewTime.GetHours();
			int32 Minutes = GrpahNewTime.GetMinutes();
			int32 Seconds = GrpahNewTime.GetSeconds();
			int32 Milliseconds = static_cast<int32>(GrpahNewTime.GetTotalMilliseconds()) % 1000;
			FString TimeString = FString::Printf(TEXT("%02d:%02d:%02d.%03d"), Hours, Minutes, Seconds, Milliseconds);
			Message += *TimeString;

			//TF -> 미래범위
			//UI에서 선택된 거 없으면 0 있으면 버튼의 값 들고와야됨.
			Message += "TF";
			Message += FString::Printf(TEXT("%d"), PredictTime);


			const TCHAR* SerializedChar = *Message;
			int32 Size = FCString::Strlen(SerializedChar) + 1;
			int32 Sent = 0;

			Socket->Send((uint8*)TCHAR_TO_UTF8(SerializedChar), Size, Sent);

			// 수신된 데이터의 크기에 맞춰 문자열 변환
			FString ReceivedMessage = ReceiveData(Socket);
			//UE_LOG(LogTemp, Log, TEXT("Port 8082 Received from server: %s"), *ReceivedMessage);
		}
		else if (Port == 8083)
		{
			FString Message; // 	 = TEXT("Message to Server 2");
			//KI
			Message += "KI";
			FString ValueToAddKI;
			for (size_t i = 0; i < Port8081_request.Num(); i++)
			{
				ValueToAddKI = Port8081_request[i] ? TEXT("1") : TEXT("0");
				Message += ValueToAddKI;
			}
			//for (size_t i = 0; i < 7; i++)
			//{
			//	FString ValueToAdd = TEXT("0");

			//	// port8081Request의 각 멤버를 순차적으로 검사
			//	switch (i)
			//	{
			//		case 0: ValueToAdd = port8081Request.CO2 ? TEXT("1") : TEXT("0"); break;
			//		case 1: ValueToAdd = port8081Request.O2 ? TEXT("1") : TEXT("0"); break;
			//		case 2: ValueToAdd = port8081Request.CO ? TEXT("1") : TEXT("0"); break;
			//		case 3: ValueToAdd = port8081Request.TEMP ? TEXT("1") : TEXT("0"); break;
			//		case 4: ValueToAdd = port8081Request.VELOCITY ? TEXT("1") : TEXT("0"); break;
			//		case 5: ValueToAdd = port8081Request.ACCEL ? TEXT("1") : TEXT("0"); break;
			//		case 6: ValueToAdd = port8081Request.FUEL ? TEXT("1") : TEXT("0"); break;
			//		default: break;
			//	}
			//	Message += ValueToAdd;
			//}

			//TN
			Message += "TN";
			int32 Hours = CurrentTime.GetHours();
			int32 Minutes = CurrentTime.GetMinutes();
			int32 Seconds = CurrentTime.GetSeconds();
			int32 Milliseconds = static_cast<int32>(CurrentTime.GetTotalMilliseconds()) % 1000;
			FString TimeString = FString::Printf(TEXT("%02d:%02d:%02d.%03d"), Hours, Minutes, Seconds, Milliseconds);
			Message += *TimeString;

			//AX 
			Message += "AX";
			for (size_t i = 0; i < this->Port8083_request.Num(); i++)
			{
				FString ValueToAdd = TEXT("0");
				ValueToAdd = Port8083_request[i] ? TEXT("1") : TEXT("0");
				Message += ValueToAdd;
			}
			//for (size_t i = 0; i < 3; i++)
			//{
			//	FString ValueToAdd = TEXT("0");

			//	// port8081Request의 각 멤버를 순차적으로 검사
			//	switch (i)
			//	{
			//	case 0: ValueToAdd = port8083Request.X ? TEXT("1") : TEXT("0"); break;
			//	case 1: ValueToAdd = port8083Request.Y ? TEXT("1") : TEXT("0"); break;
			//	case 2: ValueToAdd = port8083Request.Z ? TEXT("1") : TEXT("0"); break;
			//	default: break;
			//	}
			//	Message += ValueToAdd;
			//}

			const TCHAR* SerializedChar = *Message;
			int32 Size = FCString::Strlen(SerializedChar) + 1;
			int32 Sent = 0;
			//UE_LOG(LogTemp, Log, TEXT("Port 8082 Send from server: %s"), *Message);
			Socket->Send((uint8*)TCHAR_TO_UTF8(SerializedChar), Size, Sent);

			// 수신된 데이터의 크기에 맞춰 문자열 변환
			FString ReceivedMessage = ReceiveData(Socket);
			//UE_LOG(LogTemp, Log, TEXT("Port 8083 Received from server: %s"), *ReceivedMessage);


			if (ReceivedMessage.Contains(TEXT("Invalid request"))) // None일 때
			{
				if (!port8083ResponseAnswer.IsEmpty())
					port8083ResponseAnswer.Empty();
			}
			else 
			{
				ParshingResponsePort8083(ReceivedMessage);
			}


		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Socket is not connected"));
	}
}


FString AProtocolLibrary::ReceiveData(FSocket* Socket)
{
	if (!Socket) return FString();
	TArray<uint8> ResponseData;

	// 힙 메모리를 사용하여 동적 할당
	uint8* TempData = new uint8[ActualBufferSize]; // ActualBufferSize 크기로 힙에 메모리 할당

	int32 TotalBytesRead = 0;
	int32 BytesRead = 0;

	while (Socket->Wait(ESocketWaitConditions::WaitForRead, FTimespan::FromSeconds(0.01f)))
	{
		BytesRead = 0;
		if (Socket->Recv(TempData, ActualBufferSize, BytesRead) && BytesRead > 0)
		{
			ResponseData.Append(TempData, BytesRead);
			TotalBytesRead += BytesRead;

			uint32 PendingDataSize = 0;
			// 데이터가 더 있는지 확인하기 위해 추가 Wait를 수행
			if (!Socket->HasPendingData(PendingDataSize))
			{
				break; // 추가 데이터가 없을 때 루프 종료
			}
		}
		else
		{
			break; // 더 이상 읽을 데이터가 없을 경우 루프 종료
		}
	}

	// 힙 메모리 해제
	delete[] TempData;

	//FString ReceivedMessage = FString(BytesRead, UTF8_TO_TCHAR(ResponseData.GetData()));
	//FString ReceivedString = FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(ReceivedData.GetData())));
	FString ReceivedMessage = FString(UTF8_TO_TCHAR(ResponseData.GetData())).Left(TotalBytesRead);
	return ReceivedMessage;
}


//원래 사용하던 방법
//FString AProtocolLibrary::ReceiveData(FSocket* Socket)
//{
//	if (!Socket) return FString();
//	UE_LOG(LogTemp, Error, TEXT("Here"));
//	TArray<uint8> ReceivedData;
//	uint32 Size;
//
//	while (Socket->HasPendingData(Size))
//	{
//		UE_LOG(LogTemp, Error, TEXT("Here2"));
//		ReceivedData.SetNumUninitialized(FMath::Min(Size, (uint32)ActualBufferSize));
//
//		int32 Read = 0;
//		Socket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
//	}
//
//	FString ReceivedString = FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(ReceivedData.GetData())));
//	return ReceivedString;
//}