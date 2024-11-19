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

	// Attach Actor Pool Component, specify as EnemyPool
	ActorPool = CreateDefaultSubobject<UActorPool>(TEXT("EnemyPool"));
}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	if (Enemy)
	{
		ActorPool->InitializePool<AEnemyCharacter>(PoolSize, Enemy, this);
	}
}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
int32 AEnemySpawner::GetPoolSize() const
{
	return ActorPool ? ActorPool->GetPoolSize() : 0;
}

void AEnemySpawner::Spawn()
{
	AEnemyCharacter* AnEnemy = ActorPool->GetPooledActor<AEnemyCharacter>();
	if (AnEnemy)
	{
		// Set the enemy’s initial position and state
		AnEnemy->SetActorLocation(GetActorLocation());

		// Check if an AI controller is already assigned
		AAIController* AIController = Cast<AAIController>(AnEnemy->GetController());
		if (!AIController)
		{
			// Spawn a new AI controller if none is assigned
			AIController = GetWorld()->SpawnActor<AAIController>(AAIController::StaticClass());
			if (AIController)
			{
				AIController->Possess(AnEnemy);
			}
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AEnemySpawner: Unable to spawn an enemy - pool is empty."));
	}
}