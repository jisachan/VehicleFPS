// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VehicleBase.generated.h"


UCLASS()
class VEHICLEFPS_API AVehicleBase : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AVehicleBase();

protected:
	float Thrust;
	float Steering;
	FVector Velocity;
	FVector NewAcceleration;
	FVector OldAcceleration;
	FHitResult Hit;
	FVector Force;
	//rename later
	FVector AirResistance;

	UPROPERTY(EditAnywhere, meta = (Tooltip = "How much power is added to the current movement."))
		float Power = 10000.f;

	UPROPERTY(EditAnywhere, meta = (Tooltip = "How much mass the vehicle has, in kilograms."))
		float Mass = 1000.f;

	UPROPERTY(EditAnywhere, meta = (Tooltip = "The radius of the vehicle's turning capacity, in meters. (\nThink: If you turn a vehicle as hard as you can, it will drive in a small circle. This is that circle's radius."))
		float Radius = 5.f;

		//rename later
	UPROPERTY(EditAnywhere, meta = (Tooltip = "Multiplier for how fast the car should slow down when not pressing the throttle. Higher number slows down the car faster."))
		float SpeedReduction = 120.f;
	
	UPROPERTY(EditAnywhere, meta = (Tooltip = "Multiplier for how fast the car should slow down when breaking. Higher number slows down the car faster."))
		float BreakPower = 230.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);
	
	void SlowDown();

	void SetVerletPosition(float DeltaTime, FVector MovementForce);

	void SetVelocity(float DeltaTime);

	void SetAcceleration();

	void StoreAcceleration();

	void SetAirResistance(float speedMultiplier);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Break();
private:
};
