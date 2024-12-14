// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GundamSideProject/Projectiles/MissileManager.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyPlayer.generated.h"

UCLASS()
class GUNDAMSIDEPROJECT_API AMyPlayer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyPlayer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Jumping")
	bool bIsJumping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Jumping")
	float JumpHoldTime;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Jumping")
	float MaxJumpHoldTime;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	/* -----------------------------------------------------
	* Unreal Properties
	* -----------------------------------------------------
	*/
	UPROPERTY(EditAnywhere)
		AMissileManager* missileManager;

	/* -----------------------------------------------------
	* Unreal Functions
	* -----------------------------------------------------
	*/
	UFUNCTION(BlueprintCallable, Category = "Test Functions")
	void ShootMissile();

	
};
