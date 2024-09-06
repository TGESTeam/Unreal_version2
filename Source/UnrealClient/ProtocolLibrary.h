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
			// ��� ����� false�� �ʱ�ȭ
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
	struct Port8082_request { // ���� ���� ����
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
			// ��� ����� false�� �ʱ�ȭ
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

	int32 FutureTimeAlpha; // seconds ������ �� �ʵ��� �̷�����

	// Response ���䰪(�̷�)�� TArray�� ����
	TMap<KindPV, TArray<float>> TransformFutureDataResponse8082;

private:


	int32 Port8081;
	int32 Port8082;
	int32 Port8083;

	// ���� ������ ���� ����
	FSocket* Socket8081;
	FSocket* Socket8082;
	FSocket* Socket8083;

	// �������� ���� ���䰪�� ����
	FString Response8081;
	FString Response8082;
	FString Response8083;


	// �޽����� �ֱ������� ������ ���� Ÿ�̸� ����
	float TimeSinceLastSend;

	// ������ �ʱ�ȭ�ϰ� ������ �����ϴ� �Լ�
	void ConnectToServer(FSocket*& Socket, const FString& ServerAddress, int32 Port);

	// �޽����� ������ ������ �Լ�
	void SendMessageToServer(FSocket* Socket, int32 Port);

	
};
