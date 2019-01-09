// Fill out your copyright notice in the Description page of Project Settings.

#include "PuzzlePlatformsGameInstance.h"

#include "Engine/Engine.h"
#include "EngineGlobals.h"

#define print(text) \
	if (GEngine)    \
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::White, text)

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Hello, Constructor"));
	print("Hello, Constructor");
}

void UPuzzlePlatformsGameInstance::Host()
{
	print("Host");

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr))
		return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}

void UPuzzlePlatformsGameInstance::Init()
{
	UE_LOG(LogTemp, Warning, TEXT("Hello, Init"));
	print("Hello, Init");
}

void UPuzzlePlatformsGameInstance::Join(const FString& IpAddress)
{
	print(FString::Printf(TEXT("Joining %s"), *IpAddress));

	UWorld* World = GetWorld();

	if (!ensure(World != nullptr))
		return;

	World->ServerTravel("/Game/ThirdPersonCPP/Maps/ThirdPersonExampleMap?listen");
}