// Fill out your copyright notice in the Description page of Project Settings.


#include "GundamSideProject/Player/HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	MaxHealth = 100;
	CurrentHealth = MaxHealth;
	IsDead = false;
	IsBlocking = false;
	IsInterruptible = false;
	IsInvincible = false;
	
}

// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
bool UHealthComponent::CheckDeath()
{
	if (CurrentHealth <= 0)
	{
		IsDead = true;
		OnDeath.Broadcast();
		return true;
	}
	return false;
}
float UHealthComponent::Heal(float HealAmount)
{
	if (CurrentHealth < MaxHealth && !IsDead)
	{
		// Prevents Healing from surpassing MaxHealth 
		CurrentHealth = FMath::Clamp(CurrentHealth += HealAmount, 0, MaxHealth);
	}
	return CurrentHealth;
	
}




// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

