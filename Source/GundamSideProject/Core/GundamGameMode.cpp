// Fill out your copyright notice in the Description page of Project Settings.


#include "GundamGameMode.h"
#include "GundamSideProject/Enemies/EnemyCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GundamSideProject/Spawners/EnemySpawner.h"
#include "Kismet/GameplayStatics.h"
TArray<AActor*> EnemySpawners;
AGundamGameMode::AGundamGameMode()
{
	static ConstructorHelpers::FClassFinder<ACharacter> PlayerCharacterBP(TEXT("/Game/Blueprints/BP_Player"));
	if (PlayerCharacterBP.Class != NULL)
	{
		DefaultPawnClass = PlayerCharacterBP.Class;
	}
}
void AGundamGameMode::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemySpawner::StaticClass(), EnemySpawners);
}
void AGundamGameMode::SpawnEnemy()
{
	Cast<AEnemySpawner>(EnemySpawners[0])->Spawn();
}



