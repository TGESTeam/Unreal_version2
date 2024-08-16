// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "UnrealClientEnum.h"
#include "AllStateWidgetBFL.generated.h"

/**
 * 
 */
UCLASS()
class UNREALCLIENT_API UAllStateWidgetBFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

	UFUNCTION(Blueprintcallable, Category="SetNowPVData")
	static void SetNowPVData(KindPV selectedPV);

	
};
