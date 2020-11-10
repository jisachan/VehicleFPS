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

	Force = GetActorForwardVector() * Thrust * Power;
	//Todo: Make car slow down to a stop when releasing W or S
	if (Thrust == 0)
	{
		SlowDown();
		UE_LOG(LogTemp, Warning, TEXT("thrustie: %f"), Thrust);
	}
	//Todo: Make "Break" method with break button.
	//Todo: Make drift when break and accelarate at the same time

	SetVerletPosition(DeltaTime, Force);

	// delta angle = velocity * delta time / radius

	float RotationAngle = Velocity.Size() * DeltaTime / Radius * Steering;
	UE_LOG(LogTemp, Warning, TEXT("%f"), RotationAngle);
	FQuat RotationDelta(GetActorUpVector(), RotationAngle);
	//rotate the velocity, cool ^^
	Velocity = RotationDelta.RotateVector(Velocity);
	AddActorWorldRotation(RotationDelta);
	
	if (Hit.IsValidBlockingHit())
	{
		UE_LOG(LogTemp, Warning, TEXT("Collision Hit With %s"), *Hit.GetActor()->GetName());
	}
}

void AVehicleBase::SetVerletPosition(float DeltaTime, FVector MovementForce)
{
	FVector VerletPosition = (Velocity * DeltaTime * 100) + (OldAcceleration * DeltaTime * DeltaTime * 0.5);
	SetAcceleration();
	SetVelocity(DeltaTime);
	StoreAcceleration();

	//move to new location And check for collision
	AddActorWorldOffset(VerletPosition, true, &Hit);
}

void AVehicleBase::SetVelocity(float DeltaTime)
{
	Velocity += (OldAcceleration + NewAcceleration) * (DeltaTime * 0.5);
}

void AVehicleBase::SetAcceleration()
{
	NewAcceleration = Force / Mass; // Force = Mass * Acceleration
}

void AVehicleBase::StoreAcceleration()
{
	OldAcceleration = NewAcceleration;
}

void AVehicleBase::SetAirResistance(float speedMultiplier)
{
	AirResistance = -Velocity.GetSafeNormal() * FMath::Pow(Velocity.Size(),2) * speedMultiplier;
}

void AVehicleBase::SlowDown()
{
	SetAirResistance(SpeedReduction);
	Force += AirResistance;
}

// Called to bind functionality to input
void AVehicleBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AVehicleBase::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AVehicleBase::MoveRight);
	PlayerInputComponent->BindAction("Break", IE_Pressed, this, &AVehicleBase::Break);

}

void AVehicleBase::Break()
{
	SetAirResistance(BreakPower);
	Force += AirResistance;
}

void AVehicleBase::MoveForward(float Value)
{
	Thrust = Value;
}

void AVehicleBase::MoveRight(float Value)
{
	Steering = Value;
}