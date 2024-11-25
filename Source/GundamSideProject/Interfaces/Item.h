// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class GUNDAMSIDEPROJECT_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	FString Name;
	FString Description;
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PickUp();
	virtual void Drop();
};
