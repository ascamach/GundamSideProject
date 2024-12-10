// Fill out your copyright notice in the Description page of Project Settings.


#include "GundamSideProject/Player/MyPlayer.h"

// Sets default values
AMyPlayer::AMyPlayer()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsJumping = false;
	JumpHoldTime = 0.0f;
	MaxJumpHoldTime = 1.0f;

	
}

// Called when the game starts or when spawned
void AMyPlayer::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("Calling BeginPlay() from myPlayer"));

	missileManager = Cast<AMissileManager>(UGameplayStatics::GetActorOfClass(GetWorld(), AMissileManager::StaticClass()));
}

// Called every frame
void AMyPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMyPlayer::ShootMissile() {
	UE_LOG(LogTemp, Display, TEXT("Calling testFunction() from myPlayer"));
	// AMissileManager* testMissileManager = NewObject<AMissileManager>();

	missileManager->shootMissile();
}

