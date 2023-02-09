// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	//FString Name = GetName();

	//UE_LOG(LogTemp, Display, TEXT("Begin Play: %s"), *Name);
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);

	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	//Send Platform back if gone too far
		//Reverse direction of motion if gone too far
	if (ShouldPlatformReturn())
	{
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		//Move Platform forwards
		//Get current location of platform
	FVector CurrentLocation = GetActorLocation();
		//Add vector to that location
	CurrentLocation += PlatformVelocity * DeltaTime;
		//Set Location
	SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(PlatformRotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	//Check how far the platform has moved
	return GetDistanceTraveled() > MoveDistance;
}

float AMovingPlatform::GetDistanceTraveled() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}





