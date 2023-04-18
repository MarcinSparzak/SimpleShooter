// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	HudWidget = CreateWidget(this, HudClass);

	if (HudWidget != nullptr)
	{
		HudWidget->AddToViewport();
	}
}

void AMyPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	UUserWidget* EndScreen;
	HudWidget->RemoveFromViewport();
	if (bIsWinner)
	{
		EndScreen = CreateWidget(this, WinScreenClass);
		
	}
	else {
		EndScreen = CreateWidget(this, LoseScreenClass);
	}

	if (EndScreen != nullptr)
	{
		EndScreen->AddToViewport();
	}
	
	GetWorldTimerManager().SetTimer(TimerHandle,this, &APlayerController::RestartLevel, RestartDelay );
}

