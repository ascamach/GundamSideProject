// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GundamGameMode.generated.h"

/**
 * 
 */
UCLASS()
class GUNDAMSIDEPROJECT_API AGundamGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AGundamGameMode();
protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
private:
private:
	FTimerHandle SpawnTimerHandle;
	UFUNCTION(BlueprintCallable) void SpawnEnemy();
};
