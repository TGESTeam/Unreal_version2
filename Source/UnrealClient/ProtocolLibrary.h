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
	TArray<bool> Port8081_request;

	//���õ� ��
	int32 SelectedValue;
	void setPort8081_requestPV(int32 index, KindPV selectedPV);
	void setPort8081_requestPVAllFalse();


	//Port8081 �󵵰�
	TArray<double> port8081ResponseAnswer;
	void ParshingResponsePort8081(FString &ReceivedMessage);

	//---------------------------------------------------------

	//Port8082 Request
	int32 PredictTime = 0;

	TArray<bool> Port8082_request;

	void setPort8082_request(int32 index, KindPV selectedPV);


	//struct Port8082_request { // ���� ���� ����
	//	bool CO2 = false;
	//	bool O2 = false;
	//	bool CO = false;
	//	bool TEMP = false;
	//	bool VELOCITY = false;
	//	bool ACCEL = false;
	//	bool FUEL = false;
	//};

	//Port8082_request port8082Request;

	//------------------------------------


	//Port8083 Request
	TArray<bool> Port8083_request;
	void setPort8083_request(int32 index, FloorPlanPV seletedPV);
	void setPort8083_requestPVAllFalse();


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

private:


	int32 Port8081;
	int32 Port8082;
	int32 Port8083;

	// ���� ������ ���� ����
	FSocket* Socket8081;
	FSocket* Socket8082;
	FSocket* Socket8083;

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
