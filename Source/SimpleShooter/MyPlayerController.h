// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;
protected:
	virtual void BeginPlay() override;
private:
	UPROPERTY(EditAnywhere)
		float RestartDelay = 5.f;

	FTimerHandle TimerHandle;

	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> LoseScreenClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> WinScreenClass;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class UUserWidget> HudClass;
	
	UPROPERTY()
	UUserWidget* HudWidget;
};
