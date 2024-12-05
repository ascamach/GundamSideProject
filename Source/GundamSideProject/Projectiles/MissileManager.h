// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GundamSideProject/Projectiles/HomingMissile.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MissileManager.generated.h"

UCLASS()
class GUNDAMSIDEPROJECT_API AMissileManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMissileManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/* -----------------------------------------------------
	* Unreal Functions
	* -----------------------------------------------------
	*/
	UFUNCTION(BlueprintCallable, Category = "Missile Manager Functions")
		TArray<AActor*> findHomingTargets();

	UFUNCTION(BlueprintCallable, Category = "Missile Manager Functions")
		void shootMissile();

	UFUNCTION(BlueprintCallable, Category = "Missile Manager Functions")
		void testFunction();

	/* -----------------------------------------------------
	* Unreal Properties
	* -----------------------------------------------------
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Homing Missile")
		TSubclassOf<AHomingMissile> missileToSpawn;
};
