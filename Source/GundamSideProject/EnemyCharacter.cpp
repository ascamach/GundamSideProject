// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"

AEnemyCharacter::AEnemyCharacter() : AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bIsJumping = false;
	JumpHoldTime = 0.0f;
	MaxJumpHoldTime = 1.0f;
	
	// Default Values 
	Health = 100;
	Energy = 500;
	
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
/*
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
*/
void AEnemyCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	if(Controller != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Movement Vector: %s"), *MovementVector.ToString());
		const FRotator CameraRotation = GetCameraRotation();
		const FRotator YawRotation(0, CameraRotation.Yaw, 0);

		// Get forward direction based on character's facing direction
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        
		// Get right direction based on character's facing direction
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
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
FRotator AEnemyCharacter::GetCameraRotation() const
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// Return the controller's camera rotation, which could come from any camera setup
		return PC->PlayerCameraManager->GetCameraRotation();
	}
	return FRotator::ZeroRotator;
}
void AEnemyCharacter::FollowPlayer()
{
	
}


