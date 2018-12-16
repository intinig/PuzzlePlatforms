// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    FVector Location = GetActorLocation();

    if (((Location.X >= 660.0) && speed > 0) || ((Location.X <= 120.0) && speed < 0)) {
        speed = speed * -1;
    }   
    
    Location += FVector(speed * DeltaTime, 0, 0);
    
    SetActorLocation(Location);
}