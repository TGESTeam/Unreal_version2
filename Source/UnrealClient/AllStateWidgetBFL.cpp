// Fill out your copyright notice in the Description page of Project Settings.


#include "AllStateWidgetBFL.h"

void UAllStateWidgetBFL::SetNowPVData(KindPV selectedPV) {
	UE_LOG(LogTemp, Log, TEXT("----------------------> SetNowData Opened!!! [%d]"), (int32) selectedPV);

	if (selectedPV == CO2) {
		UE_LOG(LogTemp, Log, TEXT("----> Permeate CO2!!"));
	}
	else if(selectedPV == O2){
		UE_LOG(LogTemp, Log, TEXT("----> It's safe here!!"));
	}
	
	UE_LOG(LogTemp, Log, TEXT("----> Where is my selectedPV?"));
}