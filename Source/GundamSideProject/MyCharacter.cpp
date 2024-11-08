// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacter.h"

// Sets default values
AMyCharacter::AMyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 0;
	Energy = 0;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Switch to EnhancedInput
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

/* Implement the Attack function
void AMyCharacter::Attack()
{
	
}
*/

// Implement the Move function
void AMyCharacter::Move(const FInputActionValue& Value)
{
	
}

// Override the Jump function
void AMyCharacter::Jump()
{
	Super::Jump();
	
}


void AMyCharacter::StopJumping()
{
	Super::StopJumping();
	
}