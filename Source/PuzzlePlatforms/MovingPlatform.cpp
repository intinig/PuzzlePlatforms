// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform() {
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);

    FVector Location = GetActorLocation();

    if (((Location.X >= 660.0) && Speed > 0) || ((Location.X <= 120.0) && Speed < 0)) {
        Speed = Speed * -1;
    }   
    
    Location += FVector(Speed * DeltaTime, 0, 0);
    
    SetActorLocation(Location);
}