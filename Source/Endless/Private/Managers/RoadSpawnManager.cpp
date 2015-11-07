// Fill out your copyright notice in the Description page of Project Settings.

#include "Endless.h"
#include "RoadSpawnManager.h"


// Sets default values
ARoadSpawnManager::ARoadSpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}


// Called when the game starts or when spawned
void ARoadSpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARoadSpawnManager::SpawnSwitch()
{
	int32 Chance = FMath::RandRange(0, 100);
	switch (SpawnedType)
	{
	case ETileTypes::EC_S1:
		if (Chance < 11)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_S1);
			return;
		}
		else if (Chance < 36)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_L1);
			return;
		}
		else if (Chance < 61)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_R1);
			return;
		}
		else if (Chance < 81)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_C1);
			return;
		}
		else if (Chance < 88)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_O1);
			return;
		}
		else if (Chance < 95)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_O2);
			return;
		}
		else if (Chance <= 100)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_O3);
			return;
		}
		break;
	case ETileTypes::EC_O1:
		if (Chance < 21)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_S1);
			return;
		}
		else if (Chance < 51)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_C1);
			return;
		}
		else if (Chance < 66)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_L1);
			return;
		}
		else if (Chance < 81)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_R1);
			return;
		}
		else if (Chance <= 100)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_O2);
			return;
		}
		break;
	case ETileTypes::EC_O2:
		if (Chance < 21)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_S1);
			return;
		}
		else if (Chance < 43)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_C1);
			return;
		}
		else if (Chance < 60)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_L1);
			return;
		}
		else if (Chance < 81)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_R1);
			return;
		}
		else if (Chance <= 100)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_O3);
			return;
		}
		break;
	case ETileTypes::EC_O3:
		if (Chance < 41)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_S1);
			return;
		}
		else if (Chance < 81)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_C1);
			return;
		}
		else if (Chance <= 100)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_O1);
			return;
		}
		break;
	case ETileTypes::EC_L1:
		if (Chance < 50)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_S1);
			return;
		}
		else if (Chance <= 100)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_C1);
			return;
		}
		break;
	case ETileTypes::EC_R1:
		if (Chance < 50)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_S1);
			return;
		}
		else if (Chance <= 100)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_C1);
			return;
		}
		break;
	case ETileTypes::EC_C1:
		if (Chance < 31)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_S1);
			return;
		}
		else if (Chance < 41)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_O1);
			return;
		}
		else if (Chance < 51)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_O2);
			return;
		}
		else if (Chance < 61)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_O3);
			return;
		}
		else if (Chance < 71)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_L1);
			return;
		}
		else if (Chance < 81)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_R1);
			return;
		}
		else if (Chance <= 100)
		{
			ARoadSpawnManager::SpawnTile(ETileTypes::EC_C1);
			return;
		}
		break;
	default:
		break;
	}

}
AActor* ARoadSpawnManager::SpawnTile(ETileTypes TypeToSpawn)
{
	UWorld* const world = GetWorld();

	if (world)
	{
		TArray<TSubclassOf<class ABaseRoadTile>> BaseTile;
		for (FTileStruct& TileStruct : RoadTileArray)
		{
			if (TileStruct.TileType== TypeToSpawn)
			{
				BaseTile.Add(TileStruct.Tile);
			}	
		}
		int32 numElements = BaseTile.Num();
		int32 index = FMath::RandRange(0, numElements - 1);
		if (BaseTile.IsValidIndex(index))
		{
			if (BaseTile[index])
			{
				ABaseRoadTile* RoadTileTemp = world->SpawnActor<ABaseRoadTile>(BaseTile[index], NextSpawnPoint, NextSpawnPointRotaion);
				NextSpawnPoint = RoadTileTemp->NextSpawnPoint;
				NextSpawnPointRotaion = RoadTileTemp->NextSpawnPointRotaion;
				return RoadTileTemp;
			}
		}
		
	}
	return NULL;
}
// Called every frame
void ARoadSpawnManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

