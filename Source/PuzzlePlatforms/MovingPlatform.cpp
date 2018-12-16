// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();

    if (HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }

    GlobalStartLocation = GetActorLocation();
    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);

}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasAuthority())
    {
        float distance = FVector::Dist(GetActorLocation(), GlobalTargetLocation);
        
        if (distance < 10) {
            FVector SwitchLocation = GlobalStartLocation;
            GlobalStartLocation = GlobalTargetLocation;
            GlobalTargetLocation = SwitchLocation;
        }

        FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();        
        
        FVector Location = GetActorLocation() + Direction * Speed * DeltaTime;
        
        SetActorLocation(Location);
    }
}