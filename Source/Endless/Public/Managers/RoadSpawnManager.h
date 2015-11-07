// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Enums/EndlessEnums.h"
#include "RoadSpawnManager.generated.h"

UCLASS()
class ENDLESS_API ARoadSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:

	/************************************************************************/
	/*						Tiles Blueprint Vars                            */
	/************************************************************************/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Tiles)
		TArray<FTileStruct> RoadTileArray;
	

	UPROPERTY()
		ETileTypes SpawnedType;
	UPROPERTY()
		FVector NextSpawnPoint;
	UPROPERTY()
		FRotator NextSpawnPointRotaion;

public:	
	// Sets default values for this actor's properties
	ARoadSpawnManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SpawnSwitch();
	

	AActor* SpawnTile(ETileTypes TypeToSpawn);
	
	
};
