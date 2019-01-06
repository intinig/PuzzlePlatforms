// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

#define print(text) \
    if (GEngine)    \
    GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White, text)

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);
}

void AMovingPlatform::AddActiveTrigger()
{
    ActiveTriggers++;
}

void AMovingPlatform::RemoveActiveTrigger()
{
    if (ActiveTriggers > 0)
    {
        ActiveTriggers--;
    }
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

    if (ActiveTriggers > 0)
    {
        if (HasAuthority())
        {
            FVector Location = GetActorLocation();
            float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
            float JourneyTravelled = (Location - GlobalStartLocation).Size();

            if (JourneyTravelled >= JourneyLength)
            {
                FVector SwitchLocation = GlobalStartLocation;
                GlobalStartLocation = GlobalTargetLocation;
                GlobalTargetLocation = SwitchLocation;
            }

            FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();

            SetActorLocation(Location + Direction * Speed * DeltaTime);
        }
    }
}