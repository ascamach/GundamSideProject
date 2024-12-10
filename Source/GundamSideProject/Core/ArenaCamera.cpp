// Fill out your copyright notice in the Description page of Project Settings.


#include "ArenaCamera.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/SpringArmComponent.h"
#include "GundamSideProject/Enemies/EnemyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"

AArenaCamera::AArenaCamera()
{
	PrimaryActorTick.bCanEverTick = true;
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	// Set the desired arm length and angle for a top-down view
	SpringArm->TargetArmLength = 800.0f;
	SpringArm->SetRelativeRotation(FRotator(-75.0f, 0.0f, 0.0f)); // Tilt downward for top-down angle
	SpringArm->bDoCollisionTest = false; 
	SpringArm->bEnableCameraLag = true; 
	SpringArm->CameraLagSpeed = 3.0f;

	GetCameraComponent()->SetupAttachment(SpringArm);

	// Default values for camera behavior
	CameraSpeed = 5.0f;
	ZoomSpeed = 3.0f;
	//CameraOffset = FVector(0.0f, 0.0f, 500.0f);
	MinZoomDistance = 300.0f;
	MaxZoomDistance = 600.0f;

	// Load the Boss class if necessary
	static ConstructorHelpers::FClassFinder<ACharacter> EnemyBP(TEXT("/Game/Boss/BP_Boss.BP_Boss_C"));
	if (EnemyBP.Succeeded())
	{
		BossClass = EnemyBP.Class;
	}
}

void AArenaCamera::Tick(float DeltaTime)
{
	PrimaryActorTick.bCanEverTick = true;
	
	Super::Tick(DeltaTime);
	const ACharacter* Player1 = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	if (BossClass)
	{
		const ACharacter* Enemy = Cast<ACharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), BossClass));

		// Use TrackPlayers and RotateCamera with the found Player and Enemy
		TrackPlayers(Player1, Enemy, DeltaTime);
		RotateCamera(Player1, Enemy);
	}
}

void AArenaCamera::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(0.0f, 0.0f, 1200.0f));
}
void AArenaCamera::TrackPlayers(const ACharacter* Player1, const ACharacter* Player2, float DeltaTime)
{
	if (!Player1 || !Player2) return;

	// Get the midpoint between players
	const FVector Player1Location = Player1->GetActorLocation();
	const FVector Player2Location = Player2->GetActorLocation();

	// Check if the players are far enough apart to move the camera
	const float DistanceBetweenPlayers = FVector::Distance(Player1Location, Player2Location);
	
	const FVector MidPoint = (Player1Location + Player2Location) / 2;

	// Adjust the camera's FOV based on the distance between players
	const float DesiredFOV = FMath::Clamp(FMath::GetMappedRangeValueClamped(FVector2D(MaxZoomDistance, MinZoomDistance), FVector2D(MaxFOV, MinFOV), DistanceBetweenPlayers), MinFOV, MaxFOV);
	
	if (GetCameraComponent())
	{
		GetCameraComponent()->FieldOfView = FMath::FInterpTo(GetCameraComponent()->FieldOfView, DesiredFOV, DeltaTime, ZoomSpeed);
	}
}
void AArenaCamera::RotateCamera(const ACharacter* Player1, const ACharacter* Player2)
{
	if (!Player1 || !Player2) return;
	const float Radius = 2000.0f;
	const float Speed = 0.05f;
	
	const FVector MidPoint = (Player1->GetActorLocation() + Player2->GetActorLocation()) / 2;
	
	const float Time = GetWorld()->GetTimeSeconds();

	
	FVector NewCameraPosition;
	NewCameraPosition.X = MidPoint.X + Radius * FMath::Cos(Time * Speed);
	NewCameraPosition.Y = MidPoint.Y + Radius * FMath::Sin(Time * Speed);
	NewCameraPosition.Z = GetActorLocation().Z;
	
	SetActorLocation(NewCameraPosition);

	const FRotator CurrentRotation = GetActorRotation();
	
	// Calculates the LookAtRotation towards the midpoint of the players
	const FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(NewCameraPosition, MidPoint);

	// Preserves the current pitch and prevents the camera from bouncing with players' jump 
	const FRotator FinalRotation = FRotator(CurrentRotation.Pitch, LookAtRotation.Yaw, CurrentRotation.Roll);
	
	SetActorRotation(FinalRotation);
}
