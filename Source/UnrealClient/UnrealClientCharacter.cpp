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

	// ProtocolLibrary �̱��� �ν��Ͻ� ��������
	ProtocolLibraryInstance = AProtocolLibrary::GetInstance(GetWorld());
	if (!ProtocolLibraryInstance)
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to get ProtocolLibrary instance."));
	}

	// ���� ���� ������ ���� ũ�⿡ �°� ����
	float VoxelSpacingX = VoxelSize.X;
	float VoxelSpacingY = VoxelSize.Y;
	float VoxelSpacingZ = VoxelSize.Z;

	  // ī�޶��� ��ġ ��������
	FVector CameraLocation = GetFirstPersonCameraComponent()->GetComponentLocation();

	// X, Y �� �߾� �ε��� ��� 
	//¦�� �� ��
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
		- FVector(CenterIndexX * VoxelSpacingX, CenterIndexY * VoxelSpacingY, 0.0f);  // X, Y �߾� ����
	StartLocation.Z = 0.0f;  // �� ���̷� ����
	
	UE_LOG(LogTemp, Warning, TEXT("StartLocation : %f , %f, %f"), StartLocation.X, StartLocation.Y, StartLocation.Z);

	// ���� ���� �� �迭�� ����
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
					SpawnedVoxels.Add(SpawnedVoxel);  // �迭�� �߰�
				}
				else
				{
					UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to spawn Voxel at location: %s"), *VoxelLocation.ToString());
				}
			}
		}
	}

	// �׸��� ���� ��ġ ����
	this->GridStartLocation = StartLocation;
	//Z�� ����
	CenterIndexZ = FMath::FloorToInt((CameraLocation.Z - GridStartLocation.Z) / VoxelSpacingZ);

	//CurrentLocationStatus.Reserve(KIND_PV_LENGTH);
	CurrentLocationStatus.Init(0.0f, 7);
}

void AUnrealClientCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// ���� ���� �� �̱��� �ν��Ͻ� ����
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

	//���� ���� ������ ���� ũ�⿡ �°� ����
	float VoxelSpacingX = VoxelSize.X;
	float VoxelSpacingY = VoxelSize.Y;
	float VoxelSpacingZ = VoxelSize.Z;

	// ���� ī�޶� ��ġ ��������
	FVector CameraLocation = GetFirstPersonCameraComponent()->GetComponentLocation();

	if (ProtocolLibraryInstance) // ��Ʈ 8081 LO �� �־��ֱ�
	{
		ProtocolLibraryInstance->PlayerLocation = CameraLocation;
	}


	// ���� �÷��̾��� X, Y �ε��� ��� (�߾��� ��������)
	int32 IndexX = FMath::FloorToInt((CameraLocation.X - GridStartLocation.X) / VoxelSpacingX);
	int32 IndexY = FMath::FloorToInt((CameraLocation.Y - GridStartLocation.Y) / VoxelSpacingY);
	int32 IndexZ = FMath::FloorToInt((CameraLocation.Z - GridStartLocation.Z) / VoxelSpacingZ);
	//UE_LOG(LogTemplateCharacter, Log, TEXT("CenterIndexZ: %d, IndexZ : %d"), CenterIndexZ, IndexZ);


	// ���� ĳ������ Z�� ��ġ ��������
	float CurrentZLocation = GetActorLocation().Z;

	// Z���� ��ȭ���� ��� (���� Z�� ��ġ - �ʱ� Z�� ��ġ)
	
	// X �Ǵ� Y �࿡�� �߾ӿ��� ����ų� Z���� ��ȭ�� ��� ���� ��ġ ������Ʈ
	if (IndexX != CenterIndexX || IndexY != CenterIndexY || IndexZ != CenterIndexZ)
	{
		// X, Y �̵��� ���� GridStartLocation �̵� ��� (Z�� ��ȭ��Ű�� ����)
		FVector GridMovement = FVector(
			(IndexX - CenterIndexX) * VoxelSpacingX,
			(IndexY - CenterIndexY) * VoxelSpacingY,
			(IndexZ - CenterIndexZ) * VoxelSpacingZ
			//0.0f  // Z���� ���⼭ ��ȭ��Ű�� ����
		);
		GridStartLocation += GridMovement;

		// ��� ���� ��ġ ������Ʈ
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
						//// ZOffset�� �ݿ��Ͽ� ���� ��ġ ����
						//VoxelLocation.Z += ZOffset;
						SpawnedVoxels[Index]->SetActorLocation(VoxelLocation);
					}
				}
			}
		}

		// �÷��̾ �ٽ� X, Y �߾ӿ� ��ġ�ϵ��� �ε��� ����
		IndexX = CenterIndexX;
		IndexY = CenterIndexY;
		IndexZ = CenterIndexZ;
		//if (ProtocolLibraryInstance) // ��Ʈ 8081 LO �� �־��ֱ�
		//{
		//	ProtocolLibraryInstance->IndexX = (int64)IndexX;
		//	ProtocolLibraryInstance->IndexY = (int64)IndexY;
		//	ProtocolLibraryInstance->IndexZ = (int64)IndexZ;
		//}
	}


	//UE_LOG(LogTemplateCharacter, Log, TEXT("Player is at X index: %d, Y index: %d"), IndexX, IndexY);

	//UE_LOG(LogTemplateCharacter, Log, TEXT("Player is at X index: %d, Y index: %d"), IndexX, IndexY);
	// �����͸� ����Ͽ� ���� ���� ����
	int32 valueIndex = 0;
	// SpawnedVoxels�� �� class���� density�� �ְ�, ��� class�� nowpPV�� �����ϰ�
	for (AVoxel_Color* s : SpawnedVoxels)
	{
		s->nowPV = (KindPV)ProtocolLibraryInstance->SelectedValue;
		//UE_LOG(LogTemp, Log, TEXT("----------------------> SetNowData Opened!!! [%d] -----"), (int32)ProtocolLibraryInstance->SelectedValue);
		//if (!ProtocolLibraryInstance->port8081ResponseAnswer.IsEmpty())
		//{
		//	// �迭�� ���� ������ ���� �ִ��� Ȯ��
		//	if (valueIndex < ProtocolLibraryInstance->port8081ResponseAnswer.Num())
		//	{
		//		// �迭���� ���� ������ Voxel�� Density�� �Ҵ� (���� ��� Density�� double �Ӽ��� ���)
		//		s->density = ProtocolLibraryInstance->port8081ResponseAnswer[valueIndex];

		//		// ���� ������ �̵�
		//		valueIndex++;
		//	}
		//	else
		//	{
		//		// �迭�� ���� ��� �����Ǹ� �ʿ��� ��ġ

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