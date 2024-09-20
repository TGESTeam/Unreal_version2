// Fill out your copyright notice in the Description page of Project Settings.


#include "Voxel_Color.h"

// ---------- PV 데이터 설정 (순서는 KindPV의 값과 동일하다) ---------
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

// 이 class의 인스턴스에 있는 nowPV와 density를 기준으로 색깔을 구한다.
void AVoxel_Color::ChangeColor() {
    // 범위의 대한 density값의 비율의 100분의 1
    // RGBA는 각각 0~1까지의 값이 들어간다. 그래서 density의 비율을 넣음으로서 값을 표현함
    double densityPercent;

    // PV의 범위에 따른 dencity인지 검증
    //if ((DENSITY_MIN[nowPV] > density) || (DENSITY_MAX[nowPV] < density)) {
    //    UE_LOG(LogTemp, Warning, TEXT("Inputed invalid density's value!!"));
    //    return;
    //}
    // 표현될 색의 범위를 정한다. (|a| 는 절댓값을 의미한다.) 
    // (density - 최소) / (최대 - 최소) * 100 = (범위에 대한 %) 
    // Color의
    densityPercent = (density - DENSITY_MIN[nowPV]) / (DENSITY_MAX[nowPV] - DENSITY_MIN[nowPV]) * 100;

    // PV에 따른 색상 color 색깔 범위 설정
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

    // 인스턴스 설정
    //DynamicMaterial->SetVectorParameterValue(FName("Param"), FLinearColor(1, densityPercent, densityPercent, 1));
}


// 레드 ~ 화이트 범위의 Voxel 색깔 변경
void AVoxel_Color::SetColorWhiteToRed(double& densityPersent, bool reverse) {
    if (reverse) { // Red ~ White
        densityPersent = (1.0f - densityPersent);
    }

    DynamicMaterial->SetVectorParameterValue(FName("ColorParam"), FLinearColor(1.0f, densityPersent, densityPersent, 1.0f));

}

// 블루 ~ 레드 범위의 Voxel 색깔 변경 (역 가능)
void AVoxel_Color::SetColorBlueToRed(double& densityPersent, bool reverse) {
    if (reverse) {
        densityPersent = (1.0f - densityPersent); // densityPersent는 오직 0~1 사이 이므로 음수 판별x
    }
    
    FLinearColor SelectedColor;

    if (densityPersent >= 0.0f && densityPersent <= 0.25f) { // R증가, B감소
        SelectedColor = FLinearColor((densityPersent / 2), 0.0f, (1.0f - (densityPersent / 2)), 1.0f);
    }
    else if ((densityPersent > 0.25f && densityPersent <= 0.4f)) { // R 2배증가, B 2배감소 (보라색을 나타내지 않기 위해)
        SelectedColor = FLinearColor((densityPersent * 2), 0.0f, ((1.0f - densityPersent) * 2), 1.0f);
    }
    else if (densityPersent > 0.4f) { // 위의 상태를 천천히 유지시킴
        SelectedColor = FLinearColor(densityPersent, 0.0f, (1.0f - densityPersent), 1.0f);
    }

    DynamicMaterial->SetVectorParameterValue(FName("ColorParam"), SelectedColor);
}

// 화이트 ~ 블랙 범위의 Voxel 색깔 변경 (역 가능)
void AVoxel_Color::SetColorWhiteToBlack(double& densityPersent, bool reverse) {
    if (reverse) {
        densityPersent = (1.0f - densityPersent);
    }

    DynamicMaterial->SetVectorParameterValue(FName("ColorParam"), FLinearColor((1.0f - densityPersent), (1.0f - densityPersent), (1.0f - densityPersent), 1.0f));


}