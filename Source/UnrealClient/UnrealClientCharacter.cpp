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

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

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
	
	//InitialZLocation = GetActorLocation().Z; // Z�� �ʱⰪ�� 0.0���� ����
	//InitialZLocation = 98.337502; // Z�� �ʱⰪ�� 0.0���� ����
}

void AUnrealClientCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();


	UE_LOG(LogTemplateCharacter, Log, TEXT("here1"));

	UE_LOG(LogTemplateCharacter, Log, TEXT("here5"));

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

	// X, Y ��ǥ�� �߾ӿ� ������ StartLocation ���� (Z�� CameraLocation�� Z�� �״�� ���)
		// ���������� �׸��带 ����� ���� Z ��ġ�� 0���� ����
	//FVector StartLocation = FVector(CameraLocation.X - CenterIndexX * VoxelSpacingX, CameraLocation.Y - CenterIndexY * VoxelSpacingY, 0.0f);
	  // ����ڰ� �߾ӿ� ��ġ�ϵ��� StartLocation�� ����
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
	
	//Z�� ��ȭ���� ���� ��
	InitialZLocation = GetActorLocation().Z;




	//// ī�޶��� ��ġ�� ���� ��������
	////FVector CameraLocation = GetFirstPersonCameraComponent()->GetComponentLocation();
	//FRotator CameraRotation = GetFirstPersonCameraComponent()->GetComponentRotation();
	//FVector ForwardVector = CameraRotation.Vector();


	//// �׸����� �߾��� ī�޶� �տ� ������ ��ġ ����
	//FVector StartLocation = CameraLocation + ForwardVector * DistanceFromCamera;

	//// ���� ���� �� �迭�� ����
	//for (int32 x = 0; x < GridSizeX; ++x)
	//{
	//	for (int32 y = 0; y < GridSizeY; ++y)
	//	{
	//		for (int32 z = 0; z < GridSizeZ; ++z)
	//		{
	//			// X, Y, Z �࿡ ���� �׸��� ��ġ ���
	//			FVector VoxelLocation = StartLocation
	//				+ FVector(x * VoxelSpacingX, y * VoxelSpacingY, z * VoxelSpacingZ)
	//				- FVector((GridSizeX - 1) * VoxelSpacingX / 2.0f, (GridSizeY - 1) * VoxelSpacingY / 2.0f, (GridSizeZ - 1) * VoxelSpacingZ / 2.0f);

	//			// Voxel ���� �Ķ���� ����
	//			FActorSpawnParameters SpawnParams;
	//			SpawnParams.Owner = this;
	//			SpawnParams.Instigator = GetInstigator();

	//			// AVoxel_one Ŭ������ ���� ����
	//			//AVoxel_one* SpawnedVoxel = GetWorld()->SpawnActor<AVoxel_one>(AVoxel_one::StaticClass(), VoxelLocation, FRotator::ZeroRotator, SpawnParams);
	//			AVoxel_Color* SpawnedVoxel = GetWorld()->SpawnActor<AVoxel_Color>(AVoxel_Color::StaticClass(), VoxelLocation, FRotator::ZeroRotator, SpawnParams);

	//			if (SpawnedVoxel)
	//			{
	//				SpawnedVoxels.Add(SpawnedVoxel);  // �迭�� �߰�
	//			}
	//			else
	//			{
	//				UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to spawn Voxel at location: %s"), *VoxelLocation.ToString());
	//			}
	//		}
	//	}
	//}


	//-------------------------------------------------

	//// ���� ���� ������ ���� ũ�⿡ �°� ����
	//float VoxelSpacingX = VoxelSize.X;
	//float VoxelSpacingY = VoxelSize.Y;
	//float VoxelSpacingZ = VoxelSize.Z;

	//// ī�޶��� ��ġ�� ���� ��������
	//FVector CameraLocation = GetFirstPersonCameraComponent()->GetComponentLocation();
	//FRotator CameraRotation = GetFirstPersonCameraComponent()->GetComponentRotation();
	//FVector ForwardVector = CameraRotation.Vector();

	//// �׸����� �߾��� ī�޶� �տ� ������ ��ġ ����
	//FVector StartLocation = CameraLocation + ForwardVector * DistanceFromCamera;

	//// ���� ���� �� �迭�� ����
	//for (int32 x = 0; x < GridSizeX; ++x)
	//{
	//	for (int32 y = 0; y < GridSizeY; ++y)
	//	{
	//		for (int32 z = 0; z < GridSizeZ; ++z)
	//		{
	//			// X, Y, Z �࿡ ���� �׸��� ��ġ ���
	//			FVector VoxelLocation = StartLocation
	//				+ FVector(x * VoxelSpacingX, y * VoxelSpacingY, z * VoxelSpacingZ)
	//				- FVector((GridSizeX - 1) * VoxelSpacingX / 2.0f, (GridSizeY - 1) * VoxelSpacingY / 2.0f, (GridSizeZ - 1) * VoxelSpacingZ / 2.0f);

	//			// Voxel ���� �Ķ���� ����
	//			FActorSpawnParameters SpawnParams;
	//			SpawnParams.Owner = this;
	//			SpawnParams.Instigator = GetInstigator();

	//			// AVoxel_one Ŭ������ ���� ����
	//			//AVoxel_one* SpawnedVoxel = GetWorld()->SpawnActor<AVoxel_one>(AVoxel_one::StaticClass(), VoxelLocation, FRotator::ZeroRotator, SpawnParams);
	//			AVoxel_Color* SpawnedVoxel = GetWorld()->SpawnActor<AVoxel_Color>(AVoxel_Color::StaticClass(), VoxelLocation, FRotator::ZeroRotator, SpawnParams);

	//			if (SpawnedVoxel)
	//			{
	//				SpawnedVoxels.Add(SpawnedVoxel);  // �迭�� �߰�
	//			}
	//			else
	//			{
	//				UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to spawn Voxel at location: %s"), *VoxelLocation.ToString());
	//			}
	//		}
	//	}
	//}
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

	// ���� �÷��̾��� X, Y �ε��� ��� (�߾��� ��������)
	int32 IndexX = FMath::FloorToInt((CameraLocation.X - GridStartLocation.X) / VoxelSpacingX);
	int32 IndexY = FMath::FloorToInt((CameraLocation.Y - GridStartLocation.Y) / VoxelSpacingY);
	int32 IndexZ = FMath::FloorToInt((CameraLocation.Z - GridStartLocation.Z) / VoxelSpacingZ);
	UE_LOG(LogTemplateCharacter, Log, TEXT("CenterIndexZ: %d, IndexZ : %d"), CenterIndexZ, IndexZ);

	// ���� ĳ������ Z�� ��ġ ��������
 // ���� ĳ������ Z�� ��ġ ��������
	float CurrentZLocation = GetActorLocation().Z;

	// Z���� ��ȭ���� ��� (���� Z�� ��ġ - �ʱ� Z�� ��ġ)
	float ZOffset = CurrentZLocation - InitialZLocation;

	/*UE_LOG(LogTemplateCharacter, Log, TEXT("ZOffset: %f, CurrentZLocation : %f, InitialZLocation : %f"), ZOffset, CurrentZLocation, InitialZLocation);*/
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
	}





	// ------ z���� �ϱ� �ߴµ� ��ȭ���� �� ----------
	//// ���� ī�޶� ��ġ ��������
	//FVector CameraLocation = GetFirstPersonCameraComponent()->GetComponentLocation();

	//// ���� �÷��̾��� X, Y �ε��� ��� (�߾��� ��������)
	//int32 IndexX = FMath::FloorToInt((CameraLocation.X - GridStartLocation.X) / VoxelSpacingX);
	//int32 IndexY = FMath::FloorToInt((CameraLocation.Y - GridStartLocation.Y) / VoxelSpacingY);
	////int32 IndexZ = FMath::FloorToInt((CameraLocation.Z - GridStartLocation.Z) / VoxelSpacingZ);
	//UE_LOG(LogTemplateCharacter, Log, TEXT("CenterIndexZ: %d"), CenterIndexZ);

	//// ���� ĳ������ Z�� ��ġ ��������
 //// ���� ĳ������ Z�� ��ġ ��������
	//float CurrentZLocation = GetActorLocation().Z;

	//// Z���� ��ȭ���� ��� (���� Z�� ��ġ - �ʱ� Z�� ��ġ)
	//float ZOffset = CurrentZLocation - InitialZLocation;
	///*UE_LOG(LogTemplateCharacter, Log, TEXT("ZOffset: %f, CurrentZLocation : %f, InitialZLocation : %f"), ZOffset, CurrentZLocation, InitialZLocation);*/
	//// X �Ǵ� Y �࿡�� �߾ӿ��� ����ų� Z���� ��ȭ�� ��� ���� ��ġ ������Ʈ
	//if (IndexX != CenterIndexX || IndexY != CenterIndexY || !FMath::IsNearlyZero(ZOffset))
	//{
	//	// X, Y �̵��� ���� GridStartLocation �̵� ��� (Z�� ��ȭ��Ű�� ����)
	//	FVector GridMovement = FVector(
	//		(IndexX - CenterIndexX) * VoxelSpacingX,
	//		(IndexY - CenterIndexY) * VoxelSpacingY,
	//		0.0f  // Z���� ���⼭ ��ȭ��Ű�� ����
	//	);
	//	GridStartLocation += GridMovement;

	//	// ��� ���� ��ġ ������Ʈ
	//	for (int32 x = 0; x < GridSizeX; ++x)
	//	{
	//		for (int32 y = 0; y < GridSizeY; ++y)
	//		{
	//			for (int32 z = 0; z < GridSizeZ; ++z)
	//			{
	//				int32 Index = x * GridSizeY * GridSizeZ + y * GridSizeZ + z;
	//				if (SpawnedVoxels.IsValidIndex(Index) && SpawnedVoxels[Index])
	//				{
	//					FVector VoxelLocation = GridStartLocation + FVector(
	//						x * VoxelSpacingX,
	//						y * VoxelSpacingY,
	//						z * VoxelSpacingZ
	//					);
	//					// ZOffset�� �ݿ��Ͽ� ���� ��ġ ����
	//					VoxelLocation.Z += ZOffset;
	//					SpawnedVoxels[Index]->SetActorLocation(VoxelLocation);
	//				}
	//			}
	//		}
	//	}

	//	// �÷��̾ �ٽ� X, Y �߾ӿ� ��ġ�ϵ��� �ε��� ����
	//	IndexX = CenterIndexX;
	//	IndexY = CenterIndexY;
	//}


















	
	//// --- ���� �÷����� �߾� ��ġ �ε��� ���ϱ� --- z�� ���� ��
	//FVector CameraLocation = GetFirstPersonCameraComponent()->GetComponentLocation();
	//UE_LOG(LogTemplateCharacter, Log, TEXT("CameraLocation : %f, %f, %f"), CameraLocation.X, CameraLocation.Y, CameraLocation.Z);
	//UE_LOG(LogTemplateCharacter, Log, TEXT("GridStartLocation : %f, %f, %f"), GridStartLocation.X, GridStartLocation.Y, GridStartLocation.Z);;

	//// X, Y �ε��� ���
	//int32 IndexX = FMath::FloorToInt((CameraLocation.X - GridStartLocation.X) / VoxelSpacingX);
	//int32 IndexY = FMath::FloorToInt((CameraLocation.Y - GridStartLocation.Y) / VoxelSpacingY);

	//UE_LOG(LogTemplateCharacter, Log, TEXT("Player is at X index: %d, Y index: %d"), IndexX, IndexY);

	//// X, Y �ε����� (4, 4)�� ������� Ȯ��
	//// ����ڰ� �߾� ��ġ(CenterIndexX, CenterIndexY)���� ������� Ȯ��
	//if (IndexX != CenterIndexX || IndexY != CenterIndexY)
	//{
	//	// ��� ������ ����Ͽ� GridStartLocation�� �̵�
	//	FVector GridMovement = FVector((IndexX - CenterIndexX) * VoxelSpacingX, (IndexY - CenterIndexY) * VoxelSpacingY, 0.0f);
	//	GridStartLocation += GridMovement;

	//	// ��� ���� ��ġ ������Ʈ
	//	for (int32 x = 0; x < GridSizeX; ++x)
	//	{
	//		for (int32 y = 0; y < GridSizeY; ++y)
	//		{
	//			for (int32 z = 0; z < GridSizeZ; ++z)
	//			{
	//				int32 Index = x * GridSizeY * GridSizeZ + y * GridSizeZ + z;
	//				if (SpawnedVoxels.IsValidIndex(Index) && SpawnedVoxels[Index])
	//				{
	//					FVector VoxelLocation = GridStartLocation + FVector(x * VoxelSpacingX, y * VoxelSpacingY, z * VoxelSpacingZ);
	//					SpawnedVoxels[Index]->SetActorLocation(VoxelLocation);
	//				}
	//			}
	//		}
	//	}

	//	// �÷��̾ �ٽ� �߾ӿ� ��ġ�ϵ��� �ε��� ����
	//	IndexX = CenterIndexX;
	//	IndexY = CenterIndexY;
	//}
	//else
	//{
	//	UE_LOG(LogTemplateCharacter, Log, TEXT("Player is at the center position (X = %d, Y = %d)."), IndexX, IndexY);
	//}
	




	// -----  ������ ����ڸ� ���� 3D --- �� ī�޶� 

	//// ���� ���� ������ ���� ũ�⿡ �°� ����
	//float VoxelSpacingX = VoxelSize.X;
	//float VoxelSpacingY = VoxelSize.Y;
	//float VoxelSpacingZ = VoxelSize.Z;

	//// ī�޶��� ��ġ�� ���� ��������
	//FVector CameraLocation = GetFirstPersonCameraComponent()->GetComponentLocation();
	//FVector CameraForward = GetFirstPersonCameraComponent()->GetForwardVector();
	//FVector CameraRight = GetFirstPersonCameraComponent()->GetRightVector();
	//
	//FVector CameraUp = GetFirstPersonCameraComponent()->GetUpVector();

	//// �׸����� �߾��� ī�޶� �տ� ������ ��ġ ����
	//FVector GridCenterLocation = CameraLocation;// +CameraForward * DistanceFromCamera;

	//// ��� ������ ��ġ ������Ʈ
	//for (int32 x = 0; x < GridSizeX; ++x)
	//{
	//	for (int32 y = 0; y < GridSizeY; ++y)
	//	{
	//		for (int32 z = 0; z < GridSizeZ; ++z)
	//		{
	//			int32 Index = x * GridSizeY * GridSizeZ + y * GridSizeZ + z;
	//			if (SpawnedVoxels.IsValidIndex(Index) && SpawnedVoxels[Index])
	//			{
	//				// X, Y, Z �࿡ ���� �׸��� ��ġ ���
	//				FVector VoxelLocation = GridCenterLocation +
	//					(x - GridSizeX / 2) * VoxelSpacingX +
	//					(z - GridSizeZ / 2) * VoxelSpacingZ +
	//					(y - GridSizeY / 2) * VoxelSpacingY;
	//					//+ (CameraRight * (x - GridSizeX / 2) * VoxelSpacingX)
	//					//+ (CameraUp * (z - GridSizeZ / 2) * VoxelSpacingZ)
	//					//+ (CameraForward * (y - GridSizeY / 2) * VoxelSpacingY);

	//				// ���� ��ġ �� ȸ�� ���� (ȸ���� ī�޶� �ٶ󺸵��� ����)
	//				SpawnedVoxels[Index]->SetActorLocation(VoxelLocation);
	//				//SpawnedVoxels[Index]->SetActorRotation(FRotationMatrix::MakeFromX(CameraForward).Rotator());
	//			}
	//		}
	//	}
	//}

	//UE_LOG(LogTemplateCharacter, Log, TEXT("Player is at X index: %d, Y index: %d"), IndexX, IndexY);


	for (AVoxel_Color* s: SpawnedVoxels) {
	   //s->SetColorWhiteToRed(persent);
	   //s->DynamicMaterial->SetVectorParameterValue(FName("ColorParam"), FLinearColor::MakeRandomColor());
	   s->DynamicMaterial->SetVectorParameterValue(FName("ColorParam"), FLinearColor(1.0f, 0.25f, 0.25f, 1.0f));
	   s->DynamicMaterial->SetScalarParameterValue(FName("OpacityParam"), 0.01f);
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