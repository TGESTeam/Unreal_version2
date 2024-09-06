// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Networking.h"
#include "UnrealClientEnum.h"
#include "ProtocolLibrary.generated.h"

UCLASS()
class UNREALCLIENT_API AProtocolLibrary : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProtocolLibrary();
	~AProtocolLibrary();


	// Enum
	enum SeperatorEnum
	{ // 0~6
		LO,
		RO,
		VL,
		TI,
		SH,
		PV
	};

	//Port8081 Request
	struct Port8081_request {
		bool CO2 = false;
		bool O2 = false;
		bool CO = false;
		bool TEMP = false;
		bool VELOCITY = false;
		bool ACCEL = false;
		bool FUEL = false;

	
		void SetOnlyOneTrue(bool& target)
		{
			// 모든 멤버를 false로 초기화
			CO2 = false;
			O2 = false;
			CO = false;
			TEMP = false;
			VELOCITY = false;
			ACCEL = false;
			FUEL = false;

			target = true;
		}
	};

	Port8081_request port8081Request;

	//Port8082 Request
	int32 PredictTime = 0;
	struct Port8082_request { // 다중 선택 가능
		bool CO2 = false;
		bool O2 = false;
		bool CO = false;
		bool TEMP = false;
		bool VELOCITY = false;
		bool ACCEL = false;
		bool FUEL = false;
	};

	Port8082_request port8082Request;




	//Port8083 Request
	struct Port8083_request {
		bool X = false;
		bool Y = false;
		bool Z = false;


		void SetOnlyOneTrue8083(bool& target)
		{
			// 모든 멤버를 false로 초기화
			X = false;
			Y = false;
			Z = false;
			target = true;
		}
	};

	Port8083_request port8083Request;



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// singleton Destory
	static void DestroyInstance();

	static AProtocolLibrary* GetInstance(UWorld* World);

	static AProtocolLibrary* Instance;

	FString ReceiveData(FSocket* Socket);

	FVector PlayerLocation; // LO

	FTimespan CurrentTime; // TI

	int32 FutureTimeAlpha; // seconds 단위로 몇 초뒤의 미래인지

	// Response 응답값(미래)를 TArray에 저장
	TMap<KindPV, TArray<float>> TransformFutureDataResponse8082;

private:


	int32 Port8081;
	int32 Port8082;
	int32 Port8083;

	// 소켓 연결을 위한 변수
	FSocket* Socket8081;
	FSocket* Socket8082;
	FSocket* Socket8083;

	// 서버에게 받은 응답값을 저장
	FString Response8081;
	FString Response8082;
	FString Response8083;


	// 메시지를 주기적으로 보내기 위한 타이머 변수
	float TimeSinceLastSend;

	// 소켓을 초기화하고 서버에 연결하는 함수
	void ConnectToServer(FSocket*& Socket, const FString& ServerAddress, int32 Port);

	// 메시지를 서버에 보내는 함수
	void SendMessageToServer(FSocket* Socket, int32 Port);

	
};
