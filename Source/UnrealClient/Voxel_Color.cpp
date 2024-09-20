// Fill out your copyright notice in the Description page of Project Settings.


#include "Voxel_Color.h"

// ---------- PV ������ ���� (������ KindPV�� ���� �����ϴ�) ---------
//const float AVoxel_Color::DENSITY_MIN[KIND_PV_LENGTH] = \
//{-100.333333f, 25.3758f, 50.5097f, -30.32f, 77.7f, 0.0f, -100.12333f};
//
//const float AVoxel_Color::DENSITY_MAX[KIND_PV_LENGTH] = \
//{2499.99999f, 75.53f, 990.1f, 1.0f, 150.333f, 15.0f, 100.22523f};

const float AVoxel_Color::DENSITY_MIN[KIND_PV_LENGTH] = \
{-490.02975f, 0.0f, 0.00038641182f, 0.0f, -9.3120365f, -9.3120365f, 0.0f};

const float AVoxel_Color::DENSITY_MAX[KIND_PV_LENGTH] = \
{52.42731f, 8205.132f, 0.11520937f, 10.729547f, 6.755649f, 6.755649f, 0.0f};
// Sets default values
AVoxel_Color::AVoxel_Color()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    int32 NumX = 85;
    int32 NumY = 93;
    int32 NumZ = 101;

    // Set default voxel size
    //VoxelSize = FVector(14.58125f, 14.9976f, 15.2614f);
    VoxelSize = FVector(Dimensions.X / NumX, Dimensions.Y / NumY, Dimensions.Z / NumZ);

    // Create mesh component
    VoxelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VoxelColorMesh"));
    RootComponent = VoxelMesh;

    // Set the default mesh
    static ConstructorHelpers::FObjectFinder<UStaticMesh> VoxelMeshAsset(TEXT("StaticMesh'/Game/Voxel/VoxelMesh.VoxelMesh'"));
    if (VoxelMeshAsset.Succeeded())
    {
        VoxelMesh->SetStaticMesh(VoxelMeshAsset.Object);
    }

    //// Create a dynamic material instance
    //VoxelMaterial = UMaterialInstanceDynamic::Create(VoxelMesh->GetMaterial(0), this);
    //if (VoxelMaterial)
    //{
    //    VoxelMesh->SetMaterial(0, VoxelMaterial);
    //}
    // Calculate scale based on the desired size in cm
    //FVector Scale = VoxelSize / 100.0f;
    //VoxelMesh->SetWorldScale3D(Scale);

    UMeshComponent* MeshComponent = Cast<UMeshComponent>(GetComponentByClass(UMeshComponent::StaticClass()));

    DynamicMaterial = MeshComponent->CreateAndSetMaterialInstanceDynamic(0);

}

// Called when the game starts or when spawned
void AVoxel_Color::BeginPlay()
{
    Super::BeginPlay();

}

// Called every frame
void AVoxel_Color::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    //DynamicMaterial->SetVectorParameterValue(FName("ColorParam"), FLinearColor::MakeRandomColor());
    //DynamicMaterial->SetVectorParameterValue(FName("ColorParam"), FLinearColor(1.0f, 0.4f, 0.4f, 1.0f));

}

// �� class�� �ν��Ͻ��� �ִ� nowPV�� density�� �������� ������ ���Ѵ�.
void AVoxel_Color::ChangeColor() {
    // ������ ���� density���� ������ 100���� 1
    // RGBA�� ���� 0~1������ ���� ����. �׷��� density�� ������ �������μ� ���� ǥ����
    double densityPercent;

    // PV�� ������ ���� dencity���� ����
    //if ((DENSITY_MIN[nowPV] > density) || (DENSITY_MAX[nowPV] < density)) {
    //    UE_LOG(LogTemp, Warning, TEXT("Inputed invalid density's value!!"));
    //    return;
    //}
    // ǥ���� ���� ������ ���Ѵ�. (|a| �� ������ �ǹ��Ѵ�.) 
    // (density - �ּ�) / (�ִ� - �ּ�) * 100 = (������ ���� %) 
    // Color��
    densityPercent = (density - DENSITY_MIN[nowPV]) / (DENSITY_MAX[nowPV] - DENSITY_MIN[nowPV]) * 100;

    // PV�� ���� ���� color ���� ���� ����
    switch (nowPV) {
    case O2:
        SetColorWhiteToRed(densityPercent, true); // Red ~ White
        break;

    case CO2:
        SetColorWhiteToRed(densityPercent); // White ~ Red
        break;

    case CO:
        SetColorWhiteToRed(densityPercent); // White ~ Red
        break;

    case TEMP:
        SetColorBlueToRed(densityPercent, true); // Red ~ Blue
        break;

    case VELOCITY:
        SetColorBlueToRed(densityPercent); // Blue ~ Red
        break;

    case ACCEL:
        SetColorBlueToRed(densityPercent); // Blue ~ Red
        break;

    case FUEL:
        SetColorWhiteToBlack(densityPercent); // White ~ Black
        break;
    default:
        DynamicMaterial->SetVectorParameterValue(FName("ColorParam"), FLinearColor(1.0f, 0.25f, 0.25f, 1.0f));
        DynamicMaterial->SetScalarParameterValue(FName("OpacityParam"), 0.01f);
        break;
    }

    // �ν��Ͻ� ����
    //DynamicMaterial->SetVectorParameterValue(FName("Param"), FLinearColor(1, densityPercent, densityPercent, 1));
}


// ���� ~ ȭ��Ʈ ������ Voxel ���� ����
void AVoxel_Color::SetColorWhiteToRed(double& densityPersent, bool reverse) {
    if (reverse) { // Red ~ White
        densityPersent = (1.0f - densityPersent);
    }

    DynamicMaterial->SetVectorParameterValue(FName("ColorParam"), FLinearColor(1.0f, densityPersent, densityPersent, 1.0f));

}

// ��� ~ ���� ������ Voxel ���� ���� (�� ����)
void AVoxel_Color::SetColorBlueToRed(double& densityPersent, bool reverse) {
    if (reverse) {
        densityPersent = (1.0f - densityPersent); // densityPersent�� ���� 0~1 ���� �̹Ƿ� ���� �Ǻ�x
    }
    
    FLinearColor SelectedColor;

    if (densityPersent >= 0.0f && densityPersent <= 0.25f) { // R����, B����
        SelectedColor = FLinearColor((densityPersent / 2), 0.0f, (1.0f - (densityPersent / 2)), 1.0f);
    }
    else if ((densityPersent > 0.25f && densityPersent <= 0.4f)) { // R 2������, B 2�谨�� (������� ��Ÿ���� �ʱ� ����)
        SelectedColor = FLinearColor((densityPersent * 2), 0.0f, ((1.0f - densityPersent) * 2), 1.0f);
    }
    else if (densityPersent > 0.4f) { // ���� ���¸� õõ�� ������Ŵ
        SelectedColor = FLinearColor(densityPersent, 0.0f, (1.0f - densityPersent), 1.0f);
    }

    DynamicMaterial->SetVectorParameterValue(FName("ColorParam"), SelectedColor);
}

// ȭ��Ʈ ~ �� ������ Voxel ���� ���� (�� ����)
void AVoxel_Color::SetColorWhiteToBlack(double& densityPersent, bool reverse) {
    if (reverse) {
        densityPersent = (1.0f - densityPersent);
    }

    DynamicMaterial->SetVectorParameterValue(FName("ColorParam"), FLinearColor((1.0f - densityPersent), (1.0f - densityPersent), (1.0f - densityPersent), 1.0f));


}