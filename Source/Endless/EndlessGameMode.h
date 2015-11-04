// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "FloorTile.h"
#include "FloorTileCorner.h"
#include "EndlessGameMode.generated.h"

UCLASS(minimalapi)
class AEndlessGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AEndlessGameMode(const FObjectInitializer& ObjectInitializer);

	UPROPERTY()
		FVector NextSpawnPoint;
	UPROPERTY()
		FRotator NextSpawnPointRotaion;

	UPROPERTY()
		int32 Counter;
	UPROPERTY()
		int32 SpawnLimit;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Classes")
		TArray<TSubclassOf<class AFloorTile>>  RoadTile;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Classes")
		TArray<TSubclassOf<class AFloorTileCorner>>  RoadTileCorner;


public:
	virtual void BeginPlay() override;

	UFUNCTION()
		void AddFloorTile();
};



