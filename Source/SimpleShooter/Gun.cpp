// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
//#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFalshSocket"));
	
	FHitResult HitResult;
	FVector ShotDirection;

	bool bSuccess = GunTrace(HitResult, ShotDirection);

	if (bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, HitResult.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, HitResult.Location, 0.5f);

		AActor* Victim = HitResult.GetActor();
		if (Victim != nullptr)
		{

			FPointDamageEvent DamageEvent(Damage, HitResult, ShotDirection, nullptr);
			AController* OwnerController = GetOwnerController();
			if (OwnerController == nullptr) return;
			Victim->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}

	}
}

bool AGun::GunTrace(FHitResult& HitResult, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) return false;
	
	FVector VPLocation;
	FRotator VPRotator;
	OwnerController->GetPlayerViewPoint(VPLocation, VPRotator);

	ShotDirection = -VPRotator.Vector();
	FVector End = VPLocation + VPRotator.Vector() * MaxRange;

	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this);
	Params.AddIgnoredActor(GetOwner());

	return GetWorld()->LineTraceSingleByChannel(HitResult, VPLocation, End,ECollisionChannel::ECC_GameTraceChannel1, Params);
}

AController* AGun::GetOwnerController() const
{
	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return nullptr;

	return OwnerPawn->GetController();
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


