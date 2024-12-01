// Fill out your copyright notice in the Description page of Project Settings.

#include "GundamSideProject/Projectiles/MissileManager.h"

// Sets default values
AMissileManager::AMissileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMissileManager::BeginPlay()
{
	Super::BeginPlay();
	TArray<AActor*> currentTargets;
}

// Called every frame
void AMissileManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

TArray<AActor*> AMissileManager::findHomingTargets() {
	TArray<AActor*> homingTargets;
	TArray<AActor*> enemyTargets;
	
	UGameplayStatics::GetAllActorsOfClassWithTag(GetWorld(), AActor::StaticClass(), "Enemy", enemyTargets);

	for (int i = 0; i != enemyTargets.Num(); i++) {
		AActor* currentEnemy = enemyTargets[i];

		USceneComponent* sceneComp = Cast<USceneComponent>(currentEnemy->FindComponentByClass(USceneComponent::StaticClass()));
		if (sceneComp->IsVisible()) {
			homingTargets.Add(currentEnemy);

			//Debugging
			UE_LOG(LogTemp, Display, TEXT("Current index in array: %d"), (i));
			UE_LOG(LogTemp, Display, TEXT("Adding enemy to homing targets arry: %s"), (*currentEnemy->GetName()));
		}
	};

	return homingTargets;
}

void AMissileManager::shootMissile() {
	UE_LOG(LogTemp, Display, TEXT("Calling shootMissile() from missile manager"));
	
	FActorSpawnParameters spawnParams;

	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	// currentTargets = findHomingTargets();

	const FVector Location = GetActorLocation();
	const FRotator Rotation = GetActorRotation();

	UE_LOG(LogTemp, Display, TEXT("Calling shootMissile() from missile manager"));
	GetWorld()->SpawnActor<AActor>(missileToSpawn, Location, Rotation, spawnParams);
}

void AMissileManager::testFunction() {
	UE_LOG(LogTemp, Display, TEXT("Calling testFunction() from missile manager"));
}
