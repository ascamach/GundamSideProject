// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Spawner.h"
#include "EnemySpawner.generated.h"

/**
 * 
 */
UCLASS()
class GUNDAMSIDEPROJECT_API AEnemySpawner : public ASpawner
{
	GENERATED_BODY()
public:
	AEnemySpawner();
	virtual void Spawn() override;
	
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "Spawning") TSubclassOf<class AEnemyCharacter> Enemy;
};
