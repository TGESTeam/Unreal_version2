// Fill out your copyright notice in the Description page of Project Settings.


#include "ProtocolLibrary.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/DateTime.h" //Time 
#include "HAL/PlatformProcess.h" // For FPlatformProcess::Sleep


AProtocolLibrary* AProtocolLibrary::Instance = nullptr;
int32 ActualBufferSize = 0; // �ʱⰪ ����

// Sets default values
AProtocolLibrary::AProtocolLibrary()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Socket8081 = nullptr;
	Socket8082 = nullptr;
	Socket8083 = nullptr;
	TimeSinceLastSend = 0.0f;

	// �� ��Ʈ�� �ʱ�ȭ
	Port8081 = 8081;
	Port8082 = 8082;
	Port8083 = 8083;

}

// �̱��� �ν��Ͻ��� ��ȯ�ϴ� �Լ�
AProtocolLibrary* AProtocolLibrary::GetInstance(UWorld* World)
{
	if (Instance == nullptr)
	{
		Instance = World->SpawnActor<AProtocolLibrary>(AProtocolLibrary::StaticClass());
	}
	return Instance;
}

// �̱��� �ν��Ͻ��� ��������� �����ϴ� �Լ�
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


}

// Called when the game starts or when spawned
void AProtocolLibrary::BeginPlay()
{
	Super::BeginPlay();

	// �� ���� ������ ����
	ConnectToServer(Socket8081, TEXT("127.0.0.1"), 8081);
	ConnectToServer(Socket8082, TEXT("127.0.0.1"), 8082);
	ConnectToServer(Socket8083, TEXT("127.0.0.1"), 8083);

	////// ������ �غ�Ǿ����� Ȯ��
	if ((Socket8081 && Socket8081->GetConnectionState() == SCS_Connected) && \
		(Socket8082 && Socket8082->GetConnectionState() == SCS_Connected) && \
		(Socket8083 && Socket8083->GetConnectionState() == SCS_Connected))
	{
		// �ִ� ���� ũ�⸦ ã�� ���� �ʱⰪ�� ���� ����
		int32 DesiredBufferSize = 1024 * 1024; // 1MB���� ����
		int32 IncrementSize = 1024 * 1024; // 1MB�� ����

		// �ִ� ���� ũ�⸦ ã�� ����
		while (true)
		{
			int32 PreviousBufferSize = ActualBufferSize;
			Socket8081->SetReceiveBufferSize(DesiredBufferSize, ActualBufferSize);

			// ������ ���� ũ�Ⱑ ������ �����ϸ� �ִ� ũ�⿡ ������ ������ ����
			if (ActualBufferSize == PreviousBufferSize)
			{
				break;
			}

			// ���� �õ� ũ�� ����
			DesiredBufferSize += IncrementSize;

			// ���� ��ġ: �ʹ� ū ���� �õ����� �ʵ��� ���� (��: 64MB)
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

	// 2�ʸ��� �޽��� ����
	if (TimeSinceLastSend >= 2.0f)
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
			for (size_t i = 0; i < 7; i++)
			{
				FString ValueToAdd = TEXT("0");

				// port8081Request�� �� ����� ���������� �˻�
				switch (i)
				{
					case 0: ValueToAdd = port8081Request.CO2 ? TEXT("1") : TEXT("0"); break;
					case 1: ValueToAdd = port8081Request.O2 ? TEXT("1") : TEXT("0"); break;
					case 2: ValueToAdd = port8081Request.CO ? TEXT("1") : TEXT("0"); break;
					case 3: ValueToAdd = port8081Request.TEMP ? TEXT("1") : TEXT("0"); break;
					case 4: ValueToAdd = port8081Request.VELOCITY ? TEXT("1") : TEXT("0"); break;
					case 5: ValueToAdd = port8081Request.ACCEL ? TEXT("1") : TEXT("0"); break;
					case 6: ValueToAdd = port8081Request.FUEL ? TEXT("1") : TEXT("0"); break;
					default: break;
				}
				Message += ValueToAdd;
			}

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

			UE_LOG(LogTemp, Log, TEXT("Message Status: %s"), *Message);
			Socket->Send((uint8*)TCHAR_TO_UTF8(SerializedChar), Size, Sent);

			// ���ŵ� �������� ũ�⿡ ���� ���ڿ� ��ȯ
			FString ReceivedMessage = ReceiveData(Socket);
			UE_LOG(LogTemp, Log, TEXT("Received from server: %s"), *ReceivedMessage);
		}
		else if (Port == 8082)
		{
			FString Message; // 	 = TEXT("Message to Server 2");
			//KI
			Message += "KI";
			for (size_t i = 0; i < 7; i++) // �ߺ� ����
			{
				FString ValueToAdd = TEXT("0");

				// port8081Request�� �� ����� ���������� �˻�
				switch (i)
				{
					case 0: ValueToAdd = port8082Request.CO2 ? TEXT("1") : TEXT("0"); break;
					case 1: ValueToAdd = port8082Request.O2 ? TEXT("1") : TEXT("0"); break;
					case 2: ValueToAdd = port8082Request.CO ? TEXT("1") : TEXT("0"); break;
					case 3: ValueToAdd = port8082Request.TEMP ? TEXT("1") : TEXT("0"); break;
					case 4: ValueToAdd = port8082Request.VELOCITY ? TEXT("1") : TEXT("0"); break;
					case 5: ValueToAdd = port8082Request.ACCEL ? TEXT("1") : TEXT("0"); break;
					case 6: ValueToAdd = port8082Request.FUEL ? TEXT("1") : TEXT("0"); break;
					default: break;
				}
				Message += ValueToAdd;
			}


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

			//TF -> �̷�����
			//UI���� ���õ� �� ������ 0 ������ ��ư�� �� ���;ߵ�.
			Message += "TF";
			Message += FString::Printf(TEXT("%d"), PredictTime);


			const TCHAR* SerializedChar = *Message;
			int32 Size = FCString::Strlen(SerializedChar) + 1;
			int32 Sent = 0;

			Socket->Send((uint8*)TCHAR_TO_UTF8(SerializedChar), Size, Sent);

			// ���ŵ� �������� ũ�⿡ ���� ���ڿ� ��ȯ
			FString ReceivedMessage = ReceiveData(Socket);
			UE_LOG(LogTemp, Log, TEXT("Received from server: %s"), *ReceivedMessage);
		}
		else if (Port == 8083)
		{
			FString Message; // 	 = TEXT("Message to Server 2");
			//KI
			Message += "KI";
			for (size_t i = 0; i < 7; i++)
			{
				FString ValueToAdd = TEXT("0");

				// port8081Request�� �� ����� ���������� �˻�
				switch (i)
				{
					case 0: ValueToAdd = port8081Request.CO2 ? TEXT("1") : TEXT("0"); break;
					case 1: ValueToAdd = port8081Request.O2 ? TEXT("1") : TEXT("0"); break;
					case 2: ValueToAdd = port8081Request.CO ? TEXT("1") : TEXT("0"); break;
					case 3: ValueToAdd = port8081Request.TEMP ? TEXT("1") : TEXT("0"); break;
					case 4: ValueToAdd = port8081Request.VELOCITY ? TEXT("1") : TEXT("0"); break;
					case 5: ValueToAdd = port8081Request.ACCEL ? TEXT("1") : TEXT("0"); break;
					case 6: ValueToAdd = port8081Request.FUEL ? TEXT("1") : TEXT("0"); break;
					default: break;
				}
				Message += ValueToAdd;
			}

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
			for (size_t i = 0; i < 3; i++)
			{
				FString ValueToAdd = TEXT("0");

				// port8081Request�� �� ����� ���������� �˻�
				switch (i)
				{
				case 0: ValueToAdd = port8083Request.X ? TEXT("1") : TEXT("0"); break;
				case 1: ValueToAdd = port8083Request.Y ? TEXT("1") : TEXT("0"); break;
				case 2: ValueToAdd = port8083Request.Z ? TEXT("1") : TEXT("0"); break;
				default: break;
				}
				Message += ValueToAdd;
			}

			const TCHAR* SerializedChar = *Message;
			int32 Size = FCString::Strlen(SerializedChar) + 1;
			int32 Sent = 0;

			Socket->Send((uint8*)TCHAR_TO_UTF8(SerializedChar), Size, Sent);

			// ���ŵ� �������� ũ�⿡ ���� ���ڿ� ��ȯ
			FString ReceivedMessage = ReceiveData(Socket);
			UE_LOG(LogTemp, Log, TEXT("Received from server: %s"), *ReceivedMessage);
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

	// �� �޸𸮸� ����Ͽ� ���� �Ҵ�
	uint8* TempData = new uint8[ActualBufferSize]; // ActualBufferSize ũ��� ���� �޸� �Ҵ�

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
			// �����Ͱ� �� �ִ��� Ȯ���ϱ� ���� �߰� Wait�� ����
			if (!Socket->HasPendingData(PendingDataSize))
			{
				break; // �߰� �����Ͱ� ���� �� ���� ����
			}
		}
		else
		{
			break; // �� �̻� ���� �����Ͱ� ���� ��� ���� ����
		}
	}

	// �� �޸� ����
	delete[] TempData;

	//FString ReceivedMessage = FString(BytesRead, UTF8_TO_TCHAR(ResponseData.GetData()));
	//FString ReceivedString = FString(ANSI_TO_TCHAR(reinterpret_cast<const char*>(ReceivedData.GetData())));
	FString ReceivedMessage = FString(UTF8_TO_TCHAR(ResponseData.GetData())).Left(TotalBytesRead);
	return ReceivedMessage;
}


//���� ����ϴ� ���
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