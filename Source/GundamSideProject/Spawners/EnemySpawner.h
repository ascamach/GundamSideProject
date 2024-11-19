// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorPool.h"
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
	// Getter for ActorPool size
	
	UFUNCTION(BlueprintCallable, Category = "EnemySpawner")
	int32 GetPoolSize() const;
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	
	
private:
	UPROPERTY(VisibleAnywhere, Category = "Pooling")
	UActorPool* ActorPool;
	
	UPROPERTY(EditDefaultsOnly, Category = "Spawning")
	TSubclassOf<class AEnemyCharacter> Enemy;

	UPROPERTY(EditAnywhere, Category="Pooling")
	int32 PoolSize = 10;
};
