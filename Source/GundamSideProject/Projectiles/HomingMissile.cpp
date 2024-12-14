// Fill out your copyright notice in the Description page of Project Settings.


#include "GundamSideProject/Projectiles/HomingMissile.h"

AHomingMissile::AHomingMissile() {
	projectileComponent->bIsHomingProjectile = false;
	projectileComponent->InitialSpeed = 100;
	projectileComponent->HomingAccelerationMagnitude = 3000;
	projectileComponent->MaxSpeed = 1000;

	initialSpeed = 100;
	maxSpeed = 1000;
	// magnitude = 100;
}

void AHomingMissile::BeginPlay() 
{
	// Make the projectile homing if not set already

	// findHomingTargets();

	projectileComponent->InitialSpeed = initialSpeed;
	projectileComponent->MaxSpeed = maxSpeed;
	// projectileComponent->HomingAccelerationMagnitude = magnitude;

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
		FVector currentActorLocation = homingTargets[i]->GetActorLocation();
		UE_LOG(LogTemp, Display, TEXT("Current index in array: %d"), (i));
		UE_LOG(LogTemp, Display, TEXT("Current array target: %s"), (*homingTargets[i]->GetName()));
	}

	// AActor* testTarget;
	// USceneComponent* testComponent = testTarget->GetComponentByClass<USceneComponent>();
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
TArray<AActor*> AHomingMissile::testFunction2()
{
	TArray<AActor*> enemyTargets;
	TArray<AActor*> homingTargets;

	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), "Enemy", enemyTargets);

	for (int i = 0; i != enemyTargets.Num(); i++) {
		AActor* currentEnemy = enemyTargets[i];

		USceneComponent* sceneComp = Cast<USceneComponent>(currentEnemy->FindComponentByClass(USceneComponent::StaticClass()));
		if (!sceneComp->IsVisible()) {
			homingTargets.Add(currentEnemy);

			//Debugging
			UE_LOG(LogTemp, Display, TEXT("Current index in array: %d"), (i));
			UE_LOG(LogTemp, Display, TEXT("Adding enemy to homing targets arry: %s"), (*currentEnemy->GetName()));
		}
	};

	return homingTargets;
}
*/

/*
USceneComponent* AHomingMissile::testFunction4() {
	USceneComponent* testComp = Cast<USceneComponent>(FindComponentByClass(USceneComponent::StaticClass()));

	return testComp;
}

void AHomingMissile::testFunction3()
{
	return;
}

void AHomingMissile::setHomingTarget() {
	// Set the homing target, editable in BP
}
*/
