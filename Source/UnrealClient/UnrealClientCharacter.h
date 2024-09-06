// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "Voxel_one.h"
#include "Voxel_Color.h"
#include "ProtocolLibrary.h"
#include "UnrealClientCharacter.generated.h"

class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AUnrealClientCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Pawn mesh: 1st person view (arms; seen only by self) */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Mesh, meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* Mesh1P;

	/** First person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FirstPersonCameraComponent;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	UInputAction* MoveAction;
	
public:
	AUnrealClientCharacter();
		
	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* LookAction;

	struct LocationStatus { // reponse로 받은 density를 저장함 (8082)
		float CO2 = 0.0f;
		float O2 = 0.0f;
		float CO = 0.0f;
		float TEMP = 0.0f;
		float VELOCITY = 0.0f;
		float ACCEL = 0.0f;
		float FUEL = 0.0f;
	};

	static LocationStatus CurrentLocationStatus;

	static int32 futureTime;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	virtual void BeginPlay();

	virtual void Tick(float DeltaTime) override;

	// APawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


public:
	/** Returns Mesh1P subobject **/
	USkeletalMeshComponent* GetMesh1P() const { return Mesh1P; }
	/** Returns FirstPersonCameraComponent subobject **/
	UCameraComponent* GetFirstPersonCameraComponent() const { return FirstPersonCameraComponent; }
	AProtocolLibrary* GetProtocolLibrary();

private:
	AProtocolLibrary* ProtocolLibraryInstance;

	TArray<AVoxel_Color*> SpawnedVoxels;
	int32 GridSizeX = 10;
	int32 GridSizeY = 10;
	int32 GridSizeZ = 5;

	FVector VoxelSize;
	int32 NumX;
	int32 NumY;
	int32 NumZ;

	FVector GridStartLocation;

	int32 CenterIndexX;
	int32 CenterIndexY;
	int32 CenterIndexZ;

	

};

