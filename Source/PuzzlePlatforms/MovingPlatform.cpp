// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::White,text)

AMovingPlatform::AMovingPlatform()
{
    PrimaryActorTick.bCanEverTick = true;
    SetMobility(EComponentMobility::Movable);

}

void AMovingPlatform::DisableMovement() 
{
    StoredSpeed = Speed;
    Speed = 0;
}

void AMovingPlatform::EnableMovement() 
{
    Speed = StoredSpeed;
}

void AMovingPlatform::Trigger(int Step = 1)
{
    Triggers = Triggers + Step;
    print (FString::FromInt(Triggers));
    if (Triggers >= ActiveTriggers) {
        EnableMovement();
    } else {
        DisableMovement();
    }
}

void AMovingPlatform::AddActiveTrigger()
{
    this->Trigger(1);
}

void AMovingPlatform::RemoveActiveTrigger()
{
    this->Trigger(-1);
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

    if (!bFreeMovement) {
        this->DisableMovement();
    }
}

void AMovingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (HasAuthority())
    {
        FVector Location = GetActorLocation();
        float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
        float JourneyTravelled = (Location - GlobalStartLocation).Size();
        
        if (JourneyTravelled >= JourneyLength) {
            FVector SwitchLocation = GlobalStartLocation;
            GlobalStartLocation = GlobalTargetLocation;
            GlobalTargetLocation = SwitchLocation;
        }

        FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();        
        
        SetActorLocation(Location + Direction * Speed * DeltaTime);
    }
}