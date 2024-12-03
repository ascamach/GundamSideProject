// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathSignature);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class GUNDAMSIDEPROJECT_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	float CurrentHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	bool IsInvincible;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	bool IsDead;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	bool IsBlocking;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health")
	bool IsInterruptible;

	
public:
	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Event for when the character dies
	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnDeathSignature OnDeath;

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool CheckDeath();
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetCurrentHealth() const { return CurrentHealth; }
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetMaxHealth() {return  MaxHealth;}

	UFUNCTION(BlueprintCallable, Category = "Health")
	float Heal(float HealAmount);

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool GetIsInvincible() const { return IsInvincible; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetIsInvincible(bool bNewIsInvincible) { IsInvincible = bNewIsInvincible; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool GetIsDead() const { return IsDead; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetIsDead(bool bNewIsDead) { IsDead = bNewIsDead; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool GetIsBlocking() const { return IsBlocking; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetIsBlocking(bool bNewIsBlocking) { IsBlocking = bNewIsBlocking; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	bool GetIsInterruptible() const { return IsInterruptible; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	void SetIsInterruptible(bool bNewIsInterruptible) { IsInterruptible = bNewIsInterruptible; }
};
