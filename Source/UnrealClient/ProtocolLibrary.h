// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Networking.h"
#include "UnrealClientEnum.h"
#include "Voxel_Color.h"
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
	void ParshingResponsePort8081(FString& ReceivedMessage);
	//struct Port8081_request {
	//	bool CO2 = false;
	//	bool O2 = false;
	//	bool CO = false;
	//	bool TEMP = false;
	//	bool VELOCITY = false;
	//	bool ACCEL = false;
	//	bool FUEL = false;

	//
	//	void SetOnlyOneTrue(bool& target)
	//	{
	//		// ��� ����� false�� �ʱ�ȭ
	//		CO2 = false;
	//		O2 = false;
	//		CO = false;
	//		TEMP = false;
	//		VELOCITY = false;
	//		ACCEL = false;
	//		FUEL = false;

	//		target = true;
	//	}
	//};

	//Port8081_request port8081Request;

	// ---------------------------------------

	//Port8082 Request
	int32 PredictTime = 0;
	TArray<bool> Port8082_request;
	void setPort8082_request(int32 index, KindPV selectedPV);
	//int32 PredictTime = 0;
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

	   // ���ؽ� ��� �߰�
	FCriticalSection Mutex;
	FCriticalSection Mutex2;
	bool shouldTriggerEvent = false; // �̺�Ʈ Ʈ���� �÷���

	int32 CompletedIterations = 0; // ��ȸ �Ϸ� Ƚ�� ī����
	static const int32 MaxIterations = 10000; // �ִ� ��ȸ ��

	TArray<bool> Port8083_request;
	void setPort8083_request(int32 index, FloorPlanPV seletedPV);
	void setPort8083_requestPVAllFalse();

	int32 UpdateCounter; // ������Ʈ ī����


	//Port8083 �󵵰�
	int32 checkSetImageColorBtn;
	TArray<double> port8083ResponseAnswer;
	TArray<double> port8083Answer;
	//FEvent* AnswerSizeReachedEvent; // �̺�Ʈ ������ ����

	void ParshingResponsePort8083(FString& ReceivedMessage);
	FLinearColor GetLienarColor(double& density, int32 selectedPVIndex);
	FLinearColor SetColorWhiteToRedCrossSection(double& density, bool reverse = false);
	FLinearColor SetColorBlueToRedCrossSection(double& density, bool reverse = false);
	FLinearColor SetColorWhiteToBlackCrossSection(double& density, bool reverse = false);
	//Port8083 �ܸ鵵 Į�� ����

	//struct Port8083_request {
	//	bool X = false;
	//	bool Y = false;
	//	bool Z = false;


	//	void SetOnlyOneTrue8083(bool& target)
	//	{
	//		// ��� ����� false�� �ʱ�ȭ
	//		X = false;
	//		Y = false;
	//		Z = false;
	//		target = true;
	//	}
	//};

	//Port8083_request port8083Request;



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


	int32 port8082X;
	int32 port8082Y;
	int32 port8082Z;

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
