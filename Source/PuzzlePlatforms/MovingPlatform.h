// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

  public:
	AMovingPlatform();

	UFUNCTION(BlueprintCallable)
	void Trigger(int Step);

	UFUNCTION(BlueprintCallable)
	void AddActiveTrigger();

	UFUNCTION(BlueprintCallable)
	void RemoveActiveTrigger();


	// The speed at which platform moves (m/s)
	UPROPERTY(EditAnywhere)
	float Speed = 50;

	// Target location for the platform
	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetLocation;

  protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

  private:
	FVector GlobalTargetLocation;
	FVector GlobalStartLocation;

	float StoredSpeed = 0;

	UPROPERTY(EditAnywhere)
	int ActiveTriggers = 1;

	int Triggers = 0;

	void EnableMovement();
	void DisableMovement();
};
