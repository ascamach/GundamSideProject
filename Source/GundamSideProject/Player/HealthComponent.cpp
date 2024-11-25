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
}
void UHealthComponent::TakeDamage(int32 DamageAmount)
{
	if(DamageAmount <= 0)
	{
		return;
	}
	
	CurrentHealth = FMath::Clamp(CurrentHealth - DamageAmount, 0, MaxHealth);
	
	UE_LOG(LogTemp, Warning, TEXT("Character has taken %d damage! Current Health: %d"), DamageAmount, CurrentHealth);
	CheckDeath();
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();
	
}
void UHealthComponent::CheckDeath()
{
	if (CurrentHealth <= 0)
	{
		OnDeath.Broadcast();		
	}
}



// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

