// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingMissile.h"

void AHomingMissile::BeginPlay() 
{
	// Make the projectile homing if not set already
	projectileComponent->bIsHomingProjectile = false;

	Super::BeginPlay();
}

/*
void AHomingMissile::setHomingTarget() {
	// Set the homing target, editable in BP
}
*/
