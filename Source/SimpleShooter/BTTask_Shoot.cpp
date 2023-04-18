// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "Shooter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	Super::ExecuteTask(OwnerComp, NodeMemory);
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	else
	{
		AShooter* Shooter = Cast<AShooter>(AIController->GetPawn());
		if (Shooter == nullptr)
		{
			return EBTNodeResult::Failed;
		}
		else
		{
			Shooter->Shoot();
			return EBTNodeResult::Succeeded;
		}
	}
	
	return EBTNodeResult::Failed;


}
