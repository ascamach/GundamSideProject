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

	UFUNCTION(BlueprintCallable, Category = "Missile Properties")
		void findHomingTargets();

	UFUNCTION(BlueprintCallable, Category = "Missile Properties")
	int testFunction(int a, int b);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USceneComponent* HomingTargets;
};
