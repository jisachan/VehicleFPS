// Fill out your copyright notice in the Description page of Project Settings.


#include "VehicleBase.h"

// Sets default values
AVehicleBase::AVehicleBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVehicleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVehicleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector MovementForce = GetActorForwardVector() * Throttle * MovementPower;
	FVector VerletPosition = (Velocity * DeltaTime * 100) + (OldAcceleration * DeltaTime * DeltaTime * 0.5);
	NewAcceleration = MovementForce / Mass; // Force = Mass * Acceleration
	Velocity += (OldAcceleration + NewAcceleration) * (DeltaTime * 0.5);
	OldAcceleration = NewAcceleration;

	FHitResult Hit;
	AddActorWorldOffset(VerletPosition, true, &Hit);
	if (Hit.IsValidBlockingHit())
	{
		UE_LOG(LogTemp, Warning, TEXT("Collision Hit With %s"), *Hit.GetActor()->GetName());
	}

}

// Called to bind functionality to input
void AVehicleBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AVehicleBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVehicleBase::MoveRight);

}

void AVehicleBase::MoveForward(float Value)
{
	Throttle = Value;
}

void AVehicleBase::MoveRight(float Value)
{
	Steering = Value;
}