// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "AIController.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Kismet/GameplayStatics.h"

AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bIsJumping = false;
	JumpHoldTime = 0.0f;
	MaxJumpHoldTime = 1.0f;
	
	// Default Values 
	
	AggressionLevel = 0;

	// Default Movement Values, can be edited within editor
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()-> JumpZVelocity = 300.0f;
	GetCharacterMovement()-> AirControl = 0.35f;
	GetCharacterMovement()-> MaxWalkSpeed = 500.0f;
	GetCharacterMovement()-> MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()-> BrakingDecelerationWalking = 2000.0f;
	GetCharacterMovement()-> BrakingDecelerationFalling = 1500.0f;
	
}
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}
void AEnemyCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
	const ACharacter* Player1 = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	FollowPlayer(Player1);
	if (bIsJumping)
	{
		JumpHoldTime += DeltaTime;

		// Allow upward velocity for a limited time
		if (JumpHoldTime < MaxJumpHoldTime)
		{
			// Apply additional upward force to simulate extended jump
			GetCharacterMovement()->Velocity.Z += GetCharacterMovement()->JumpZVelocity * DeltaTime;
		}
	}

}
void AEnemyCharacter::Jump()
{
	if (!bIsJumping){
		Super::Jump();
		bIsJumping = true; 
		JumpHoldTime = 0.0f; 
	}
}
void AEnemyCharacter::StopJumping()
{
	bIsJumping = false; 
	Super::StopJumping(); 
}

void AEnemyCharacter::FollowPlayer(const ACharacter* Player)
{
	if(!Player) return;

	const FVector PlayerLocation = Player->GetActorLocation();
	UE_LOG(LogTemp, Warning, TEXT("Following player to location: %s"), *PlayerLocation.ToString());

	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
		// Nav Mesh Volume is required for MoveToLocation 
		UE_LOG(LogTemp, Warning, TEXT("AI Controller Casted Properly"));
		AIController->MoveToLocation(PlayerLocation);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No AI Controller found."));
		const FVector Direction = (PlayerLocation - GetActorLocation()).GetSafeNormal();
		AddMovementInput(Direction);
	}
}


