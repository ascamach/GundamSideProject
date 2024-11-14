// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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
};
