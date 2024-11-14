// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/GameplayStatics.h"

#include "CoreMinimal.h"
#include "Projectile.h"
#include "HomingMissile.generated.h"

/**
 * 
 */
UCLASS()
class GUNDAMSIDEPROJECT_API AHomingMissile : public AProjectile
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

	// Unreal Functions
	UFUNCTION(BlueprintCallable, Category = "Missile Properties")
		void findHomingTargets();
	
	UFUNCTION(BlueprintCallable, Category = "Missile Properties")
		int testFunction(int a, int b);

	UFUNCTION(BlueprintCallable, Category = "Missile Properties")
		TArray<AActor*> testFunction2();

	// Unreal Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* HomingTargets;
};
