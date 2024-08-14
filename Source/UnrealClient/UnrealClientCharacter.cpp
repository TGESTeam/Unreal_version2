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

	// ī�޶��� ��ġ�� ���� ��������
	FVector CameraLocation = GetFirstPersonCameraComponent()->GetComponentLocation();
	FRotator CameraRotation = GetFirstPersonCameraComponent()->GetComponentRotation();
	FVector ForwardVector = CameraRotation.Vector();

	// �׸����� �߾��� ī�޶� �տ� ������ ��ġ ����
	FVector StartLocation = CameraLocation + ForwardVector * DistanceFromCamera;

	// ���� ���� �� �迭�� ����
	for (int32 x = 0; x < GridSizeX; ++x)
	{
		for (int32 y = 0; y < GridSizeY; ++y)
		{
			for (int32 z = 0; z < GridSizeZ; ++z)
			{
				// X, Y, Z �࿡ ���� �׸��� ��ġ ���
				FVector VoxelLocation = StartLocation
					+ FVector(x * VoxelSpacingX, y * VoxelSpacingY, z * VoxelSpacingZ)
					- FVector((GridSizeX - 1) * VoxelSpacingX / 2.0f, (GridSizeY - 1) * VoxelSpacingY / 2.0f, (GridSizeZ - 1) * VoxelSpacingZ / 2.0f);

				// Voxel ���� �Ķ���� ����
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();

				// AVoxel_one Ŭ������ ���� ����
				AVoxel_one* SpawnedVoxel = GetWorld()->SpawnActor<AVoxel_one>(AVoxel_one::StaticClass(), VoxelLocation, FRotator::ZeroRotator, SpawnParams);

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


	//// ���� ���� ������ ���� ũ�⿡ �°� ����
	//float VoxelSpacingY = VoxelSize.Y;
	//float VoxelSpacingZ = VoxelSize.Z;

	//// ī�޶��� ��ġ�� ���� ��������
	//FVector CameraLocation = GetFirstPersonCameraComponent()->GetComponentLocation();
	//FRotator CameraRotation = GetFirstPersonCameraComponent()->GetComponentRotation();
	//FVector ForwardVector = CameraRotation.Vector();

	//// CameraLocation ���
	//UE_LOG(LogTemp, Log, TEXT("CameraLocation: %s"), *CameraLocation.ToString());

	//// CameraRotation ���
	//UE_LOG(LogTemp, Log, TEXT("CameraRotation: Pitch: %f, Yaw: %f, Roll: %f"), CameraRotation.Pitch, CameraRotation.Yaw, CameraRotation.Roll);

	//// ForwardVector ���
	//UE_LOG(LogTemp, Log, TEXT("ForwardVector: %s"), *ForwardVector.ToString());

	//// �׸����� �߾��� ī�޶� �տ� ������ ��ġ ����
	//FVector StartLocation = CameraLocation + ForwardVector * DistanceFromCamera;

	//UE_LOG(LogTemp, Log, TEXT("StartLocation: %s"), *StartLocation.ToString());

	//// ���� ���� �� �迭�� ����
	//for (int32 i = 0; i < GridSizeY; ++i)
	//{
	//	for (int32 j = 0; j < GridSizeZ; ++j)
	//	{
	//		// Y�� Z �࿡ ���� �׸��� ��ġ ���
	//		FVector VoxelLocation = StartLocation + FVector(0.0f, i * VoxelSpacingY, j * VoxelSpacingZ)
	//			- FVector(0.0f, (GridSizeY - 1) * VoxelSpacingY / 2.0f, (GridSizeZ - 1) * VoxelSpacingZ / 2.0f);

	//		// Voxel ���� �Ķ���� ����
	//		FActorSpawnParameters SpawnParams;
	//		SpawnParams.Owner = this;
	//		SpawnParams.Instigator = GetInstigator();

	//		// AVoxel_one Ŭ������ ���� ����
	//		AVoxel_one* SpawnedVoxel = GetWorld()->SpawnActor<AVoxel_one>(AVoxel_one::StaticClass(), VoxelLocation, FRotator::ZeroRotator, SpawnParams);

	//		if (SpawnedVoxel)
	//		{
	//			SpawnedVoxels.Add(SpawnedVoxel);  // �迭�� �߰�
	//		}
	//		else
	//		{
	//			UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to spawn Voxel at location: %s"), *VoxelLocation.ToString());
	//		}
	//	}
	//}







	//// ���� ���� ������ ���� ũ�⿡ �°� ����
	//float VoxelSpacingY = VoxelSize.Y;
	//float VoxelSpacingZ = VoxelSize.Z;

	//// ī�޶��� ��ġ�� ���� ��������
	//FVector CameraLocation = GetFirstPersonCameraComponent()->GetComponentLocation();
	//FRotator CameraRotation = GetFirstPersonCameraComponent()->GetComponentRotation();
	//FVector ForwardVector = CameraRotation.Vector();

	//// �׸����� �߾��� ī�޶� �տ� ������ ��ġ ����
	//FVector StartLocation = CameraLocation + ForwardVector * 500.0f;

	//// ���� ���� �� �迭�� ����
	//for (int32 i = 0; i < GridSize; ++i)
	//{
	//	for (int32 j = 0; j < GridSize; ++j)
	//	{
	//		// Y�� Z �࿡ ���� �׸��� ��ġ ���
	//		FVector VoxelLocation = StartLocation + FVector(0.0f, i * VoxelSpacingY, j * VoxelSpacingZ)
	//			- FVector(0.0f, (GridSize - 1) * VoxelSpacingY / 2.0f, (GridSize - 1) * VoxelSpacingZ / 2.0f);

	//		// Voxel ���� �Ķ���� ����
	//		FActorSpawnParameters SpawnParams;
	//		SpawnParams.Owner = this;
	//		SpawnParams.Instigator = GetInstigator();

	//		// AVoxel_one Ŭ������ ���� ����
	//		AVoxel_one* SpawnedVoxel = GetWorld()->SpawnActor<AVoxel_one>(AVoxel_one::StaticClass(), VoxelLocation, CameraRotation, SpawnParams);

	//		if (SpawnedVoxel)
	//		{
	//			SpawnedVoxel->SetActorEnableCollision(false); // �浹 ��Ȱ��ȭ
	//			SpawnedVoxel->SetActorTickEnabled(false); // ƽ ��Ȱ��ȭ
	//			SpawnedVoxels.Add(SpawnedVoxel);  // �迭�� �߰�
	//		}
	//		else
	//		{
	//			UE_LOG(LogTemplateCharacter, Error, TEXT("Failed to spawn Voxel at location: %s"), *VoxelLocation.ToString());
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

	// ���� ���� ������ ���� ũ�⿡ �°� ����
	float VoxelSpacingX = VoxelSize.X;
	float VoxelSpacingY = VoxelSize.Y;
	float VoxelSpacingZ = VoxelSize.Z;

	// ī�޶��� ��ġ�� ���� ��������
	FVector CameraLocation = GetFirstPersonCameraComponent()->GetComponentLocation();
	FVector CameraForward = GetFirstPersonCameraComponent()->GetForwardVector();
	FVector CameraRight = GetFirstPersonCameraComponent()->GetRightVector();
	FVector CameraUp = GetFirstPersonCameraComponent()->GetUpVector();

	// �׸����� �߾��� ī�޶� �տ� ������ ��ġ ����
	FVector GridCenterLocation = CameraLocation + CameraForward * DistanceFromCamera;

	// ��� ������ ��ġ ������Ʈ
	for (int32 x = 0; x < GridSizeX; ++x)
	{
		for (int32 y = 0; y < GridSizeY; ++y)
		{
			for (int32 z = 0; z < GridSizeZ; ++z)
			{
				int32 Index = x * GridSizeY * GridSizeZ + y * GridSizeZ + z;
				if (SpawnedVoxels.IsValidIndex(Index) && SpawnedVoxels[Index])
				{
					// X, Y, Z �࿡ ���� �׸��� ��ġ ���
					FVector VoxelLocation = GridCenterLocation
						+ (CameraRight * (x - GridSizeX / 2) * VoxelSpacingX)
						+ (CameraUp * (z - GridSizeZ / 2) * VoxelSpacingZ)
						+ (CameraForward * (y - GridSizeY / 2) * VoxelSpacingY);

					// ���� ��ġ �� ȸ�� ���� (ȸ���� ī�޶� �ٶ󺸵��� ����)
					SpawnedVoxels[Index]->SetActorLocation(VoxelLocation);
					SpawnedVoxels[Index]->SetActorRotation(FRotationMatrix::MakeFromX(CameraForward).Rotator());
				}
			}
		}
	}

	//// ���� ���� ������ ���� ũ�⿡ �°� ����
	//float VoxelSpacingY = VoxelSize.Y;
	//float VoxelSpacingZ = VoxelSize.Z;

	//// ī�޶��� ��ġ�� ���� ��������
	//FVector CameraLocation = GetFirstPersonCameraComponent()->GetComponentLocation();
	//FVector CameraForward = GetFirstPersonCameraComponent()->GetForwardVector();
	//FVector CameraRight = GetFirstPersonCameraComponent()->GetRightVector();
	//FVector CameraUp = GetFirstPersonCameraComponent()->GetUpVector();

	//// �׸����� �߾��� ī�޶� �տ� ������ ��ġ ����
	//FVector GridCenterLocation = CameraLocation + CameraForward * DistanceFromCamera;

	//// ��� ������ ��ġ ������Ʈ
	//for (int32 i = 0; i < GridSizeY; ++i)
	//{
	//	for (int32 j = 0; j < GridSizeZ; ++j)
	//	{
	//		int32 Index = i * GridSizeZ + j;
	//		if (SpawnedVoxels.IsValidIndex(Index) && SpawnedVoxels[Index])
	//		{
	//			// Y�� Z �࿡ ���� �׸��� ��ġ ���
	//			FVector VoxelLocation = GridCenterLocation
	//				+ (CameraRight * (i - GridSizeY / 2) * VoxelSpacingY)
	//				+ (CameraUp * (j - GridSizeZ / 2) * VoxelSpacingZ);

	//			// ���� ��ġ �� ȸ�� ���� (ȸ���� ī�޶� �ٶ󺸵��� ����)
	//			SpawnedVoxels[Index]->SetActorLocation(VoxelLocation);
	//			SpawnedVoxels[Index]->SetActorRotation(FRotationMatrix::MakeFromX(CameraForward).Rotator());
	//		}
	//	}
	//}






	//// ���� ���� ������ ���� ũ�⿡ �°� ����
	//float VoxelSpacingY = VoxelSize.Y;
	//float VoxelSpacingZ = VoxelSize.Z;

	//// ī�޶��� ��ġ�� ���� ��������
	//FVector CameraLocation = GetFirstPersonCameraComponent()->GetComponentLocation();
	//FRotator CameraRotation = GetFirstPersonCameraComponent()->GetComponentRotation();
	//FVector ForwardVector = CameraRotation.Vector();

	//// �׸����� �߾��� ī�޶� �տ� ������ ��ġ ����
	//FVector StartLocation = CameraLocation + ForwardVector * 500.0f;

	//// ��� ������ ��ġ �� ȸ�� ������Ʈ
	//for (int32 i = 0; i < GridSize; ++i)
	//{
	//	for (int32 j = 0; j < GridSize; ++j)
	//	{
	//		int32 Index = i * GridSize + j;
	//		if (SpawnedVoxels.IsValidIndex(Index) && SpawnedVoxels[Index])
	//		{
	//			// Y�� Z �࿡ ���� �׸��� ��ġ ���
	//			FVector VoxelLocation = StartLocation + FVector(0.0f, i * VoxelSpacingY, j * VoxelSpacingZ)
	//				- FVector(0.0f, (GridSize - 1) * VoxelSpacingY / 2.0f, (GridSize - 1) * VoxelSpacingZ / 2.0f);
	//			SpawnedVoxels[Index]->SetActorLocation(VoxelLocation);
	//			SpawnedVoxels[Index]->SetActorRotation(CameraRotation);  // ī�޶��� ȸ�� ���⿡ ���߱�
	//		}
	//	}
	//}

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