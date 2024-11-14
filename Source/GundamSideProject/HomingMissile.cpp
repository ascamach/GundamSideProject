// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingMissile.h"

void AHomingMissile::BeginPlay() 
{
	// Make the projectile homing if not set already
	projectileComponent->bIsHomingProjectile = false;

	findHomingTargets();

	Super::BeginPlay();
}

void AHomingMissile::findHomingTargets() 
{
	UE_LOG(LogTemp, Display, TEXT("Find homing targets called"));

	// Create TArray to hold the output from UGameplayStatics
	TArray<AActor*> homingTargets;

	// Call function to get all actors with specfic tag
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), "Enemy", homingTargets);

	// -----------------------------------------------------
	// DEBUGGING PURPOSES
	// -----------------------------------------------------
	for (int i = 0; i != homingTargets.Num(); i++) {
		UE_LOG(LogTemp, Display, TEXT("Current index in array: %d"), (i));
		UE_LOG(LogTemp, Display, TEXT("Current array target: %s"), (*homingTargets[i]->GetName()));
	}
}

void AHomingMissile::Tick(float deltaTime) 
{
	Super::Tick(deltaTime);
}

int AHomingMissile::testFunction(int a, int b) 
{
	return a + b;
}

/*
void AHomingMissile::setHomingTarget() {
	// Set the homing target, editable in BP
}
*/
