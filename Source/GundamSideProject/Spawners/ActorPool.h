// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIController.h"
#include "GundamSideProject/Spawners/Spawner.h"
#include "ActorPool.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUNDAMSIDEPROJECT_API UActorPool : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UActorPool();

	template<class T>
	void InitializePool(int32 PoolSize, TSubclassOf<T> InActorClass, ASpawner* Spawner);

	template<class T>
	T* GetPooledActor();

	template<class T>
	void ReturnActorToPool(T* Actor);
	
	UFUNCTION(BlueprintCallable, Category = "Pool")
	int32 GetPoolSize() const;

protected:
	// Called when the game starts
	TArray<AActor*> ActorPool;
	
	TSubclassOf<AActor> ActorClass;

	ASpawner* PoolOwner;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
		
};
template<class T>
void UActorPool::InitializePool(int32 PoolSize, TSubclassOf<T> InActorClass, ASpawner* Spawner)
{
	// Check validity
	if (!InActorClass || !Spawner)
	{
		UE_LOG(LogTemp, Warning, TEXT("UActorPool: Invalid ActorClass or Spawner provided to InitializePool."));
		return;
	}
	
	ActorClass = InActorClass;
	PoolOwner = Spawner;

	for(int32 i = 0; i < PoolSize; i++)
	{
		T* NewActor = GetWorld()->SpawnActor<T>(ActorClass, PoolOwner->GetActorLocation(), FRotator::ZeroRotator);
		if (NewActor)
		{
			NewActor->SetActorEnableCollision(false);
			NewActor->SetActorHiddenInGame(true);
			ActorPool.Add(NewActor);
		}
	}
}

template <class T>
T* UActorPool::GetPooledActor()
{
	if(ActorPool.Num() > 0)
	{
		T* Actor = Cast<T>(ActorPool.Pop());
		Actor->SetActorEnableCollision(true);
		Actor->SetActorHiddenInGame(false);
		return Actor;
	}
	return nullptr;
}


template <class T>
void UActorPool::ReturnActorToPool(T* Actor)
{
	if (Actor)
	{
		// Stop AI movement if it has an AIController
		if (AAIController* AIController = Cast<AAIController>(Actor->GetController()))
		{
			AIController->StopMovement();
		}
		
		Actor->SetActorEnableCollision(false);
		Actor->SetActorHiddenInGame(true);
		
		// Reset position 
		Actor->SetActorLocation(PoolOwner->GetActorLocation());
		
		// Add back to pool
		ActorPool.Add(Actor);
	}
}
