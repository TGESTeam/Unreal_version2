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

	//선택된 값
	int32 SelectedValue;
	void setPort8081_requestPV(int32 index, KindPV selectedPV);
	void setPort8081_requestPVAllFalse();

	//Port8081 농도값
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
	//		// 모든 멤버를 false로 초기화
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
	//struct Port8082_request { // 다중 선택 가능
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

	   // 뮤텍스 멤버 추가
	FCriticalSection Mutex;
	FCriticalSection Mutex2;
	bool shouldTriggerEvent = false; // 이벤트 트리거 플래그

	int32 CompletedIterations = 0; // 순회 완료 횟수 카운터
	static const int32 MaxIterations = 10000; // 최대 순회 값

	TArray<bool> Port8083_request;
	void setPort8083_request(int32 index, FloorPlanPV seletedPV);
	void setPort8083_requestPVAllFalse();

	int32 UpdateCounter; // 업데이트 카운터


	//Port8083 농도값
	int32 checkSetImageColorBtn;
	TArray<double> port8083ResponseAnswer;
	TArray<double> port8083Answer;
	//FEvent* AnswerSizeReachedEvent; // 이벤트 포인터 선언

	void ParshingResponsePort8083(FString& ReceivedMessage);
	FLinearColor GetLienarColor(double& density, int32 selectedPVIndex);
	FLinearColor SetColorWhiteToRedCrossSection(double& density, bool reverse = false);
	FLinearColor SetColorBlueToRedCrossSection(double& density, bool reverse = false);
	FLinearColor SetColorWhiteToBlackCrossSection(double& density, bool reverse = false);
	//Port8083 단면도 칼러 주입

	//struct Port8083_request {
	//	bool X = false;
	//	bool Y = false;
	//	bool Z = false;


	//	void SetOnlyOneTrue8083(bool& target)
	//	{
	//		// 모든 멤버를 false로 초기화
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

	int32 FutureTimeAlpha; // seconds 단위로 몇 초뒤의 미래인지

	// Response 응답값(미래)를 TArray에 저장
	TMap<KindPV, TArray<float>> TransformFutureDataResponse8082;


	int32 port8082X;
	int32 port8082Y;
	int32 port8082Z;

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
