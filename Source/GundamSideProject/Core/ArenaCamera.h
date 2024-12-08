// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "GameFramework/SpringArmComponent.h"
#include "ArenaCamera.generated.h"

/**
 * 
 */
UCLASS()
class GUNDAMSIDEPROJECT_API AArenaCamera : public ACameraActor
{
	GENERATED_BODY()
public:
	AArenaCamera();
	void TrackPlayers(const ACharacter* Player1,  const ACharacter* Player2, float DeltaTime);
	void RotateCamera(const ACharacter* Player1, const ACharacter* Player2);
	
protected:
	virtual void Tick(float DeltaTime) override;
	virtual void BeginPlay() override;
	
private:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera", meta = (AllowPrivateAccess = "true"))
	float CameraSpeed;  

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera", meta = (AllowPrivateAccess = "true"))
	float ZoomSpeed;  

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera", meta = (AllowPrivateAccess = "true"))
	FVector CameraOffset;  

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera", meta = (AllowPrivateAccess = "true"))
	float MinZoomDistance; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Camera", meta = (AllowPrivateAccess = "true"))
	float MaxZoomDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float MaxFOV = 90.0f; 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	float MinFOV = 60.0f;


	
	TSubclassOf<ACharacter> BossClass;
};

