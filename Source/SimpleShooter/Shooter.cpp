// Fill out your copyright notice in the Description page of Project Settings.


#include "Shooter.h"
#include "Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooterGameModeBase.h"

// Sets default values
AShooter::AShooter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooter::BeginPlay()
{
	Super::BeginPlay();
	Health = MaxHealth;

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	GetMesh()->HideBoneByName(TEXT("Weapon_r"), EPhysBodyOp::PBO_None);
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

bool AShooter::IsDead() const
{
	return Health <= 0;
}

float AShooter::GetHealthPercent() const
{
	return Health/MaxHealth;
}

// Called every frame
void AShooter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &APawn::AddControllerYawInput);

	PlayerInputComponent->BindAction(TEXT("JUMP"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooter::Shoot);
}

float AShooter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float DamageApplied = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	
	DamageApplied = FMath::Min(Health, DamageApplied);
	Health -= DamageApplied;
	UE_LOG(LogTemp, Warning, TEXT("Current health: %f"), Health);

	if (IsDead())
	{
		ASimpleShooterGameModeBase* GameMode = GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		DetachFromControllerPendingDestroy();
		GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	return DamageApplied;
}

void AShooter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooter::Shoot()
{
	Gun->PullTrigger();
}



