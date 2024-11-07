// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyCharacter.h"
#include "EnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class GUNDAMSIDEPROJECT_API AEnemyCharacter : public AMyCharacter
{
	GENERATED_BODY()
public:
	AEnemyCharacter();
	//virtual void AEnemyCharacter::Tick(float DeltaTime) override;
	
protected:
	void FollowPlayer();
	// void AttackPattern();

	int AggressionLevel;
	TArray<AActor*> MyActorArray; // Will Replace with Items class
	bool bIsJumping; 
	float JumpHoldTime; 
	float MaxJumpHoldTime;
	
	virtual void Move(const FInputActionValue& Value) override;
	virtual void Jump() override;
	virtual void StopJumping() override;

	FRotator GetCameraRotation() const;
};
