// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "GameplayTagsManager.h"
#include "UnrealClientEnum.h"
#include "Voxel_Color.generated.h"

UCLASS()
class UNREALCLIENT_API AVoxel_Color : public AActor
{
	GENERATED_BODY()

public:
	AVoxel_Color();

	// ----- 변수 ----
public:
	FVector Dimensions = FVector(1633.0f, 1809.0f, 2014.0f);

	

	// PV에 따른 DENSSITY의 최소, 최댓값
	// 순서는 KindPV의 값과 동일하다
	static const float DENSITY_MIN[KIND_PV_LENGTH];
	static const float DENSITY_MAX[KIND_PV_LENGTH];

	// Voxel size
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voxel")
	FVector VoxelSize;

	// Gameplay Tags
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tags")
	FGameplayTagContainer GameplayTags;

	UMaterialInstanceDynamic* DynamicMaterial;

	KindPV nowPV;

	float density;
private:
	// Mesh component
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent* VoxelMesh;



	// ----- 함수 ----
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ChangeColor();

	// 색깔 설정
	void SetColorWhiteToRed(double& densityPersent, bool reverse = false); // White ~ Red

	void SetColorBlueToRed(double& densityPersent, bool reverse = false); // Blue ~ Red

	void SetColorWhiteToBlack(double& densityPersent, bool reverse = false); // White ~ Black
};