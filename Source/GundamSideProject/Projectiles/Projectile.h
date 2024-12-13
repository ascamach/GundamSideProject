// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/ProjectileMovementComponent.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class GUNDAMSIDEPROJECT_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	// Default parent class for all projectile related actors
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/*
	// Components for our projectile
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* projectileMesh;
		*/


	/* -----------------------------------------------------
	* Unreal Properties
	* -----------------------------------------------------
	*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UProjectileMovementComponent* projectileComponent;
};
