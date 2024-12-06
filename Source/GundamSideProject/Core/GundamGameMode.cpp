// Fill out your copyright notice in the Description page of Project Settings.


#include "GundamGameMode.h"
#include "GundamSideProject/Enemies/EnemyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GundamSideProject/Spawners/EnemySpawner.h"
#include "Kismet/GameplayStatics.h"

TArray<AActor*> EnemySpawners;
AGundamGameMode::AGundamGameMode()
{
	/*
	static ConstructorHelpers::FClassFinder<ACharacter> PlayerCharacterBP(TEXT("/Game/Blueprints/BP_Player"));
	if (PlayerCharacterBP.Succeeded())  // Use Succeeded() to check for success
	{
		DefaultPawnClass = PlayerCharacterBP.Class;
	}
	*/

	static ConstructorHelpers::FClassFinder<AActor> CameraBP(TEXT("/Game/Blueprints/BP_ArenaCamera"));
	if (CameraBP.Succeeded())
	{
		CameraClass = CameraBP.Class;
	}
}
void AGundamGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if (CameraClass)
	{
		AActor* CameraActor = GetWorld()->SpawnActor<AActor>(CameraClass);
		if (CameraActor)
		{
			APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			if (PlayerController && CameraActor)
			{
				FViewTargetTransitionParams TransitionParams;
				TransitionParams.BlendTime = 0.0f; // Instant transition
				//PlayerController->SetViewTarget(CameraActor, TransitionParams);
			}
		}
	}
	/*
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), EnemySpawners);
	// Debug log to verify spawners are found
	UE_LOG(LogTemp, Log, TEXT("Found %d enemy spawners in the level."), EnemySpawners.Num());

	// Spawns an enemy every 1 second
	GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, this, &AGundamGameMode::SpawnEnemy, 1.0f, true);
	*/
}
void AGundamGameMode::Tick(float DeltaTime)
{
	
}

void AGundamGameMode::SpawnEnemy()
{
	if (EnemySpawners.Num() > 0)
	{
		AEnemySpawner* Spawner = Cast<AEnemySpawner>(EnemySpawners[0]);
		if (Spawner->GetPoolSize() > 0)
		{
			Spawner->Spawn();
		}
	}
}