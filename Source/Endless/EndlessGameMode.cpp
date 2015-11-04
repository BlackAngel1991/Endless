// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Endless.h"
#include "EndlessGameMode.h"
#include "EndlessCharacter.h"

AEndlessGameMode::AEndlessGameMode(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
	NextSpawnPoint = FVector(0, 0, 0);
	NextSpawnPointRotaion = FRotator(0, 0, 0);
	Counter = 0;
	SpawnLimit = 7;
}
void AEndlessGameMode::AddFloorTile()
{
	UWorld* const world = GetWorld();
	if (world )
	{
		
		UE_LOG(LogTemp, Warning, TEXT("rndrange %f "), (float)SpawnLimit);
		if (Counter < SpawnLimit)
		{
			
			int32 numElements = RoadTile.Num();
			int32 index = FMath::RandRange(0, numElements - 1);
			if (RoadTile.IsValidIndex(index))
			{
				if (RoadTile[index])
				{
					//const FVector CNext = NextSpawnPoint;
					//world->SpawnActor(RoadTile, CNext, rotator);
					AFloorTile* RoadTileTemp = world->SpawnActor<AFloorTile>(RoadTile[index], NextSpawnPoint, NextSpawnPointRotaion);
					NextSpawnPoint = RoadTileTemp->NextSpawnPoint;
					NextSpawnPointRotaion = RoadTileTemp->NextSpawnPointRotaion;
					
					Counter++;
				}
			}
		}
		else
		{
			Counter = 0;
			SpawnLimit = FMath::RandRange(7, 10);
			int32 numElements = RoadTileCorner.Num();
			int32 index = FMath::RandRange(0, numElements - 1);
			if (RoadTileCorner.IsValidIndex(index))
			{
				if (RoadTileCorner[index])
				{
					//const FVector CNext = NextSpawnPoint;
					//world->SpawnActor(RoadTile, CNext, rotator);
					AFloorTileCorner* RoadTileTemp = world->SpawnActor<AFloorTileCorner>(RoadTileCorner[index], NextSpawnPoint, NextSpawnPointRotaion);
					NextSpawnPoint = RoadTileTemp->NextSpawnPoint;
					NextSpawnPointRotaion = RoadTileTemp->NextSpawnPointRotaion;
					

					
				}
			}
		}
		
		
	}
}
// Called when the game starts or when spawned
void AEndlessGameMode::BeginPlay()
{
	Super::BeginPlay();
	for (int i = 0; i < 10; i++)
	{
		AEndlessGameMode::AddFloorTile();
	}
}