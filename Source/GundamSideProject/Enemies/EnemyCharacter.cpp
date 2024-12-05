// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyCharacter.h"
#include "AIController.h"
#include "DrawDebugHelpers.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GundamSideProject/Player/HealthComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

AEnemyCharacter::AEnemyCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	bIsJumping = false;
	JumpHoldTime = 0.0f;
	MaxJumpHoldTime = 1.0f;
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
	
	// If hidden, skip processing
	if (IsHidden())
	{
		return;
	}
	
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
	const float Radius = 200.0f;
	const float AngularSpeed = 50.0f;
	const float DetectionDistance = 300.0f;
	if(!Player) return;

	
	const FVector PlayerLocation = Player->GetActorLocation();

	
	const float DistanceBetweenActors = FVector::Distance(PlayerLocation, GetActorLocation());

	if (AAIController* AIController = Cast<AAIController>(GetController()))
	{
	
		if (DistanceBetweenActors < DetectionDistance )
		{
			// Draw debug circle around the player 
			DrawDebugCircle(
				GetWorld(),
				PlayerLocation,
				Radius,
				50, // Number of segments for smoothness
				FColor::Green,
				false, // Persistent (false means it disappears after a few seconds)
				-1.0f, // Lifetime (-1 means it lasts for one frame)
				0, // Depth priority (0 is default)
				2.0f, // Line thickness
				FVector(1, 0, 0), // X axis
				FVector(0, 1, 0), // Y axis
				true // Draw a 3D circle
			);
			
			// Calculate the angle change based on angular speed
			const float AngleChange = AngularSpeed * GetWorld()->GetDeltaSeconds();
			FVector Direction = (GetActorLocation() - PlayerLocation).GetSafeNormal();
			
			const FRotator Rotation = FRotator(0, AngleChange, 0);

			// Rotate enemy direction around the player
			Direction = Rotation.RotateVector(Direction);

			// Set the new location along the circular path
			const FVector NewLocation = PlayerLocation + Direction * Radius;
			SetActorLocation(NewLocation);

			// Interpolate Rotation to reduce stuttering 
			const FRotator LookAtRotation = (PlayerLocation - GetActorLocation()).Rotation();
			SetActorRotation(FMath::RInterpTo(GetActorRotation(), LookAtRotation, GetWorld()->GetDeltaSeconds(), 3.0f));

			if (GetWorld()->GetTimerManager().IsTimerActive(DamageTimerHandle) == false)
			{
				// Start a timer to call ApplyDamage every 3 seconds
				GetWorld()->GetTimerManager().SetTimer(DamageTimerHandle, this, &AEnemyCharacter::Attack, 3.0f, true);
			}
		}
		else 
		{
			// Move directly towards the player when out of range
			AIController->MoveToLocation(PlayerLocation);
			
			// Stop applying damage when out of range
			GetWorld()->GetTimerManager().ClearTimer(DamageTimerHandle);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No AI Controller found."));
		const FVector Direction = (PlayerLocation - GetActorLocation()).GetSafeNormal();
		AddMovementInput(Direction);
	}
}
void AEnemyCharacter::Attack()
{
	// Ensure the player is valid
	if (ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		UHealthComponent* HealthComponent = Player->FindComponentByClass<UHealthComponent>();
	}
}


