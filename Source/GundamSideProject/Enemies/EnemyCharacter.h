// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class GUNDAMSIDEPROJECT_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AEnemyCharacter();
	virtual void Tick(const float DeltaTime) override;
	
protected:
	void FollowPlayer(const ACharacter* Player);
	// void AttackPattern();

	virtual void BeginPlay() override;
	int AggressionLevel;
	//TArray<AActor*> MyActorArray; // Will Replace with Items class
	bool bIsJumping; 
	float JumpHoldTime; 
	float MaxJumpHoldTime;
	
	virtual void Jump() override;
	virtual void StopJumping() override;
	
};
