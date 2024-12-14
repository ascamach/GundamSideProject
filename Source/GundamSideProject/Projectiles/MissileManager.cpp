// Fill out your copyright notice in the Description page of Project Settings.

#include "GundamSideProject/Projectiles/MissileManager.h"

#include "UObject/ConstructorHelpers.h"

// Sets default values
AMissileManager::AMissileManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FClassFinder<AHomingMissile> homingMissileBP(TEXT("/Game/Blueprints/BP_HomingMissile"));
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

	UE_LOG(LogTemp, Display, TEXT("-------------------------------------------------"));

	return homingTargets;
}

void AMissileManager::shootMissile() {
	// UE_LOG(LogTemp, Display, TEXT("Calling shootMissile() from missile manager"));

	// Variables for our function.
	/* targetsArray is the array of all enemies in the scene
	* currentTarget is our current placement in the array
	*/
	TArray<AActor*> targetsArray;
	AActor* currentTarget;

	// Set spawn parameters for missile spawn
	FActorSpawnParameters spawnParams;

	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	// Set targetsArray to our findHomingTargets return
	targetsArray = findHomingTargets();

	if (targetsArray.IsEmpty()) {
		return;
	}

	// For now, our current target is the first index of targetsArray
	currentTarget = targetsArray[0];

	// Set spawn location and rotation
	const FVector Location = GetActorLocation();
	const FRotator Rotation = GetActorRotation();

	UE_LOG(LogTemp, Display, TEXT("Calling shootMissile() from missile manager"));

	// Set missile properties BEFORE spawning
	missileToSpawn->GetDefaultObject<AHomingMissile>()->initialSpeed = 10;
	missileToSpawn->GetDefaultObject<AHomingMissile>()->maxSpeed = 0;
	// missileToSpawn->GetDefaultObject<AHomingMissile>()->magnitude = 30;

	GetWorld()->SpawnActor<AActor>(missileToSpawn, Location, Rotation, spawnParams);

	UProjectileMovementComponent* currentMissileProperties = missileToSpawn->GetDefaultObject<AHomingMissile>()->projectileComponent;

	currentMissileProperties->bIsHomingProjectile = true;
	// currentMissileProperties->InitialSpeed = 2000;
	// currentMissileProperties->MaxSpeed = 3000;
	currentMissileProperties->HomingTargetComponent = currentTarget->GetComponentByClass<USceneComponent>();

	UE_LOG(LogTemp, Display, TEXT("Current homing target: %s"), (*currentTarget->GetName()));
	UE_LOG(LogTemp, Display, TEXT("-----------------------------------------------------------"));
}

