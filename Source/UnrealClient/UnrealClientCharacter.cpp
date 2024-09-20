// Copyright Epic Games, Inc. All Rights Reserved.

#include "UnrealClientCharacter.h"
#include "UnrealClientProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Camera/PlayerCameraManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Engine/LocalPlayer.h"
#include "Engine/World.h"
#include <Kismet/GameplayStatics.h>
#include "ProtocolLibrary.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

TArray<float> AUnrealClientCharacter::CurrentLocationStatus;
int32 AUnrealClientCharacter::futureTime;

//////////////////////////////////////////////////////////////////////////
// AUnrealClientCharacter

AUnrealClientCharacter::AUnrealClientCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
		
	// Create a CameraComponent	
	FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
	FirstPersonCameraComponent->SetRelativeLocation(FVector(-10.f, 0.f, 60.f)); // Position the camera
	FirstPersonCameraComponent->bUsePawnControlRotation = true;

	// Create a mesh component that will be used when being viewed from a '1st person' view (when controlling this pawn)
	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetupAttachment(FirstPersonCameraComponent);
	Mesh1P->bCastDynamicShadow = false;
	Mesh1P->CastShadow = false;
	//Mesh1P->SetRelativeRotation(FRotator(0.9f, -19.19f, 5.2f));
	Mesh1P->SetRelativeLocation(FVector(-30.f, 0.f, -150.f));



	NumX = 85;
	NumY = 93;
	NumZ = 101;

	FVector Dimensions = FVector(1633.0f, 1809.0f, 2014.0f);
	VoxelSize = FVector(Dimensions.X / NumX, Dimensions.Y / NumY, Dimensions.Z / NumZ); // 19.2117, 19.4516, 19.9405

}

void AUnrealClientCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	UE_LOG(LogTemplateCharacter, Log, TEXT("BeginPlay"));

	// ProtocolLibrary 싱글톤 인스턴스 가져오기
	ProtocolLibraryInstance = AProtocolLibrary::GetInstance(GetWorld());
	if (!ProtocolLibraryInstance)
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to get ProtocolLibrary instance."));
	}

	// 복셀 간의 간격을 복셀 크기에 맞게 설정
	float VoxelSpacingX = VoxelSize.X;
	float VoxelSpacingY = VoxelSize.Y;
	float VoxelSpacingZ = VoxelSize.Z;

	  // 카메라의 위치 가져오기
	FVector CameraLocation = GetFirstPersonCameraComponent()->GetComponentLocation();

	// X, Y 축 중앙 인덱스 계산 
	//짝수 일 때
	if (GridSizeX % 2 == 0 && GridSizeY % 2 == 0)
	{
		CenterIndexX = GridSizeX / 2 - 1;
		CenterIndexY = GridSizeY / 2 - 1;
	}
	else 
	{
		CenterIndexX = GridSizeX / 2;
		CenterIndexY = GridSizeY / 2;
	}
	FVector StartLocation = CameraLocation
		- FVector(CenterIndexX * VoxelSpacingX, CenterIndexY * VoxelSpacingY, 0.0f);  // X, Y 중앙 맞춤
	StartLocation.Z = 0.0f;  // 땅 높이로 설정
	
	UE_LOG(LogTemp, Warning, TEXT("StartLocation : %f , %f, %f"), StartLocation.X, StartLocation.Y, StartLocation.Z);

	// 복셀 생성 및 배열에 저장
	for (int32 x = 0; x < GridSizeX; ++x)
	{
		for (int32 y = 0; y < GridSizeY; ++y)
		{
			for (int32 z = 0; z < GridSizeZ; ++z)
			{
				FVector VoxelLocation = StartLocation + FVector(x * VoxelSpacingX, y * VoxelSpacingY, z * VoxelSpacingZ);

				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();

				AVoxel_Color* SpawnedVoxel = GetWorld()->SpawnActor<AVoxel_Color>(AVoxel_Color::StaticClass(), VoxelLocation, FRotator::ZeroRotator, SpawnParams);

				if (SpawnedVoxel)
				{
					SpawnedVoxels.Add(SpawnedVoxel);  // 배열에 추가
				}
				else
				{
					UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to spawn Voxel at location: %s"), *VoxelLocation.ToString());
				}
			}
		}
	}

	// 그리드 시작 위치 저장
	this->GridStartLocation = StartLocation;
	//Z축 설정
	CenterIndexZ = FMath::FloorToInt((CameraLocation.Z - GridStartLocation.Z) / VoxelSpacingZ);

	//CurrentLocationStatus.Reserve(KIND_PV_LENGTH);
	CurrentLocationStatus.Init(0.0f, 7);
}

void AUnrealClientCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// 게임 종료 시 싱글톤 인스턴스 해제
	AProtocolLibrary::DestroyInstance();
}

AProtocolLibrary* AUnrealClientCharacter::GetProtocolLibrary()
{
	return ProtocolLibraryInstance;
}


//////////////////////////////////////////////////////////////////////////// Input

void AUnrealClientCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AUnrealClientCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AUnrealClientCharacter::Look);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input Component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

void AUnrealClientCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//복셀 간의 간격을 복셀 크기에 맞게 설정
	float VoxelSpacingX = VoxelSize.X;
	float VoxelSpacingY = VoxelSize.Y;
	float VoxelSpacingZ = VoxelSize.Z;

	// 현재 카메라 위치 가져오기
	FVector CameraLocation = GetFirstPersonCameraComponent()->GetComponentLocation();

	if (ProtocolLibraryInstance) // 포트 8081 LO 값 넣어주기
	{
		ProtocolLibraryInstance->PlayerLocation = CameraLocation;
	}


	// 현재 플레이어의 X, Y 인덱스 계산 (중앙을 기준으로)
	int32 IndexX = FMath::FloorToInt((CameraLocation.X - GridStartLocation.X) / VoxelSpacingX);
	int32 IndexY = FMath::FloorToInt((CameraLocation.Y - GridStartLocation.Y) / VoxelSpacingY);
	int32 IndexZ = FMath::FloorToInt((CameraLocation.Z - GridStartLocation.Z) / VoxelSpacingZ);
	//UE_LOG(LogTemplateCharacter, Log, TEXT("CenterIndexZ: %d, IndexZ : %d"), CenterIndexZ, IndexZ);


	// 현재 캐릭터의 Z축 위치 가져오기
	float CurrentZLocation = GetActorLocation().Z;

	// Z축의 변화량을 계산 (현재 Z축 위치 - 초기 Z축 위치)
	
	// X 또는 Y 축에서 중앙에서 벗어났거나 Z축이 변화된 경우 복셀 위치 업데이트
	if (IndexX != CenterIndexX || IndexY != CenterIndexY || IndexZ != CenterIndexZ)
	{
		// X, Y 이동에 따른 GridStartLocation 이동 계산 (Z는 변화시키지 않음)
		FVector GridMovement = FVector(
			(IndexX - CenterIndexX) * VoxelSpacingX,
			(IndexY - CenterIndexY) * VoxelSpacingY,
			(IndexZ - CenterIndexZ) * VoxelSpacingZ
			//0.0f  // Z축은 여기서 변화시키지 않음
		);
		GridStartLocation += GridMovement;

		// 모든 복셀 위치 업데이트
		for (int32 x = 0; x < GridSizeX; ++x)
		{
			for (int32 y = 0; y < GridSizeY; ++y)
			{
				for (int32 z = 0; z < GridSizeZ; ++z)
				{
					int32 Index = x * GridSizeY * GridSizeZ + y * GridSizeZ + z;
					if (SpawnedVoxels.IsValidIndex(Index) && SpawnedVoxels[Index])
					{
						FVector VoxelLocation = GridStartLocation + FVector(
							x * VoxelSpacingX,
							y * VoxelSpacingY,
							z * VoxelSpacingZ
						);
						//// ZOffset을 반영하여 복셀 위치 설정
						//VoxelLocation.Z += ZOffset;
						SpawnedVoxels[Index]->SetActorLocation(VoxelLocation);
					}
				}
			}
		}

		// 플레이어가 다시 X, Y 중앙에 위치하도록 인덱스 조정
		IndexX = CenterIndexX;
		IndexY = CenterIndexY;
		IndexZ = CenterIndexZ;
		//if (ProtocolLibraryInstance) // 포트 8081 LO 값 넣어주기
		//{
		//	ProtocolLibraryInstance->IndexX = (int64)IndexX;
		//	ProtocolLibraryInstance->IndexY = (int64)IndexY;
		//	ProtocolLibraryInstance->IndexZ = (int64)IndexZ;
		//}
	}


	//UE_LOG(LogTemplateCharacter, Log, TEXT("Player is at X index: %d, Y index: %d"), IndexX, IndexY);

	//UE_LOG(LogTemplateCharacter, Log, TEXT("Player is at X index: %d, Y index: %d"), IndexX, IndexY);
	// 포인터를 사용하여 현재 값을 추적
	int32 valueIndex = 0;
	// SpawnedVoxels의 각 class별로 density가 있고, 모든 class의 nowpPV는 동일하고
	for (AVoxel_Color* s : SpawnedVoxels)
	{
		s->nowPV = (KindPV)ProtocolLibraryInstance->SelectedValue;
		//UE_LOG(LogTemp, Log, TEXT("----------------------> SetNowData Opened!!! [%d] -----"), (int32)ProtocolLibraryInstance->SelectedValue);
		//if (!ProtocolLibraryInstance->port8081ResponseAnswer.IsEmpty())
		//{
		//	// 배열의 값이 여전히 남아 있는지 확인
		//	if (valueIndex < ProtocolLibraryInstance->port8081ResponseAnswer.Num())
		//	{
		//		// 배열에서 값을 가져와 Voxel의 Density에 할당 (예를 들어 Density가 double 속성일 경우)
		//		s->density = ProtocolLibraryInstance->port8081ResponseAnswer[valueIndex];

		//		// 다음 값으로 이동
		//		valueIndex++;
		//	}
		//	else
		//	{
		//		// 배열의 값이 모두 소진되면 필요한 조치

		//	}
		if (!ProtocolLibraryInstance->port8081ResponseAnswer.IsEmpty())
		{
			s->density = ProtocolLibraryInstance->port8081ResponseAnswer[valueIndex];
			valueIndex++;
			s->ChangeColor();
		}
		else
		{
			s->DynamicMaterial->SetVectorParameterValue(FName("ColorParam"), FLinearColor(1.0f, 0.25f, 0.25f, 1.0f));
			s->DynamicMaterial->SetScalarParameterValue(FName("OpacityParam"), 0.01f);
		}
		;
		//}
		// 
		//s->DynamicMaterial->SetVectorParameterValue(FName("ColorParam"), FLinearColor::MakeRandomColor());
		//s->DynamicMaterial->SetVectorParameterValue(FName("ColorParam"), FLinearColor(1.0f, 0.25f, 0.25f, 1.0f));
		//s->DynamicMaterial->SetScalarParameterValue(FName("OpacityParam"), 0.01f);
	}


}



void AUnrealClientCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add movement 
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void AUnrealClientCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}