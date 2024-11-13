// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemySpawner.h"

#include "AIController.h"
#include "GundamSideProject/Enemies/EnemyCharacter.h"
#include "Engine/World.h"

// Sets default values
AEnemySpawner::AEnemySpawner()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
void AEnemySpawner::Spawn()
{
	AEnemyCharacter* AnEnemy = GetWorld()->SpawnActor<AEnemyCharacter>(Enemy, RootComponent->GetComponentLocation(), RootComponent->GetComponentRotation());\
	if (AnEnemy)
	{
		// Create or assign an AI controller to the enemy
		AAIController* AIController = GetWorld()->SpawnActor<AAIController>(AAIController::StaticClass(), FVector::ZeroVector, FRotator::ZeroRotator);

		if (AIController)
		{
			// Possess the enemy character with the AI controller
			AIController->Possess(AnEnemy);
		}
	}
}