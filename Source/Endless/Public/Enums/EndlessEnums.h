// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "RoadTiles/BaseRoadTile.h"
#include "EndlessEnums.generated.h"
/**
 * 
 */
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EForwardDirection : uint8
{
	EC_X 	UMETA(DisplayName = "Fowrad is X"),
	EC_Y 	UMETA(DisplayName = "Forward is Y")

};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ECornerType : uint8
{
	EC_Left 	UMETA(DisplayName = "To Left"),
	EC_Right 	UMETA(DisplayName = "To Right"),
	EC_None		UMETA(DisplayName = "No DIrection")

};
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ETileTypes : uint8
{
	EC_S1 UMETA(DisplayName = "Straight Type 1"),
	EC_S2 UMETA(DisplayName = "Straight Type 2"),
	EC_S3 UMETA(DisplayName = "Straight Type 3"),
	EC_S4 UMETA(DisplayName = "Straight Type 4"),
	EC_C1 UMETA(DisplayName = "Coin Type 1"),
	EC_C2 UMETA(DisplayName = "Coin Type 2"),
	EC_C3 UMETA(DisplayName = "Coin Type 3"),
	EC_C4 UMETA(DisplayName = "Coin Type 4"),
	EC_O1 UMETA(DisplayName = "Obstacle Type 1"),
	EC_O2 UMETA(DisplayName = "Obstacle Type 2"),
	EC_O3 UMETA(DisplayName = "Obstacle Type 3"),
	EC_O4 UMETA(DisplayName = "Obstacle Type 4"),
	EC_L1 UMETA(DisplayName = "Left Type 1"),
	EC_L2 UMETA(DisplayName = "Left Type 2"),
	EC_R1 UMETA(DisplayName = "Right Type 1"),
	EC_R2 UMETA(DisplayName = "Right Type 2")
};
USTRUCT(BlueprintType)
struct FTileStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETileTypes TileType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class ABaseRoadTile> Tile;

	//Set
	void SetEnum(const ETileTypes NewValue)
	{
		TileType = NewValue;
	}

	//Get
	TSubclassOf<ABaseRoadTile> GetActor()
	{
		return Tile;
	}

	//Check
	bool ActorIsValid() const
	{
		if (!Tile) return false;
		return Tile->IsValidLowLevel();
	}

	//Constructor
	FTileStruct()
	{
		//Always initialize your USTRUCT variables!
		//exception is if you know the variable type has its own default constructor
		TileType = ETileTypes::EC_S1;
		Tile = NULL;
	}
};