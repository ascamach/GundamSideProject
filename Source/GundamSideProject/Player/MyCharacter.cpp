// Fill out your copyright notice in the Description page of Project Settings.


#include "GundamSideProject/Player/MyCharacter.h"
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


// Sets default values
AMyCharacter::AMyCharacter()
{
	bIsJumping = false;
	JumpHoldTime = 0.0f;
	MaxJumpHoldTime = 1.0f;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Create and initialize HealthComponent
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	GetCharacterMovement()-> JumpZVelocity = 300.0f;
	GetCharacterMovement()-> AirControl = 0.35f;
	GetCharacterMovement()-> MaxWalkSpeed = 500.0f;
	GetCharacterMovement()-> MinAnalogWalkSpeed = 20.0f;
	GetCharacterMovement()-> BrakingDecelerationWalking = 2000.0f;
	GetCharacterMovement()-> BrakingDecelerationFalling = 1500.0f;
	
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void AMyCharacter::BeginPlay()
{
	Super::BeginPlay();
	

	// Add input mapping context
	if(APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	// Bind OnDeath Event to a Function
	if (HealthComponent)
	{
		HealthComponent->OnDeath.AddDynamic(this, &AMyCharacter::OnDeath);
	}
	
}

void AMyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if(UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AMyCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AMyCharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMyCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyCharacter::Look);
		
	}
	
}

void AMyCharacter::OnDeath()
{
	// Temporary Death logic
	UE_LOG(LogTemp, Warning, TEXT("Character has died!"));
	
}

void AMyCharacter::Move(const FInputActionValue& Value)
{
	//UE_LOG(LogTemp, Warning, TEXT("Value: %s"), *Value.ToString());
	
	
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
		
		// add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
		
	}
}

void AMyCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}


// Called every frame
void AMyCharacter::Tick(float DeltaTime)
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
FRotator AMyCharacter::GetCameraRotation() const
{
	if (APlayerController* PC = Cast<APlayerController>(GetController()))
	{
		// Return the controller's camera rotation, which could come from any camera setup
		return PC->PlayerCameraManager->GetCameraRotation();
	}
	return FRotator::ZeroRotator;
}

void AMyCharacter::Jump()
{
	if (!bIsJumping)
	{
		
		Super::Jump();
		bIsJumping = true; 
		JumpHoldTime = 0.0f; 
	}
}

void AMyCharacter::StopJumping()
{
	bIsJumping = false; 
	Super::StopJumping(); 
}