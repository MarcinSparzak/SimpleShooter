// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAiController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Shooter.h"

void AShooterAiController::BeginPlay()
{
	Super::BeginPlay();	 
	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);
		/*APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
		GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), PlayerPawn->GetActorLocation());*/

		APawn* ControlledPawn = GetPawn();
		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), ControlledPawn->GetActorLocation());
	}
}

void AShooterAiController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}

bool AShooterAiController::IsDead() const
{
	AShooter* ControlledCharacter = Cast<AShooter>(GetPawn());
	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}
	return true;
}
