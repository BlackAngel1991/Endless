// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RoadTiles/BaseRoadTile.h"
#include "FloorTile.generated.h"



UCLASS()
class ENDLESS_API AFloorTile : public ABaseRoadTile
{
	GENERATED_BODY()
	
public:	




	

public:
	// Sets default values for this actor's properties
	AFloorTile();


	virtual void OnConstruction(const FTransform& Transform);

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
		void onOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &HitRes);
	virtual void onOverlapBegin_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &HitRes);


	
		void onOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void onOverlapEnd_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
	void DestroyMe();
	
};
