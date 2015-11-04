// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "RoadTiles/BaseRoadTile.h"
#include "Enums/DirectionEnums.h"
#include "FloorTileCorner.generated.h"


UCLASS()
class ENDLESS_API AFloorTileCorner : public ABaseRoadTile
{
	GENERATED_BODY()
	
public:	


	bool BoxSet;


	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Meshes")
	class UBoxComponent* TrunTrigger;



	
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "defaults")
		ECornerType CornerType;

	virtual void OnConstruction(const FTransform& Transform);

	
		void onOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &HitRes);
	virtual void onOverlapBegin_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &HitRes);
	
		void onOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void onOverlapEnd_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintNativeEvent, Category = "Spawn and Destroy")
		void onOverlapBeginTurn(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &HitRes);
	virtual void onOverlapBeginTurn_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &HitRes);
	UFUNCTION(BlueprintNativeEvent, Category = "Spawn and Destroy")
		void onOverlapEndTurn(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void onOverlapEndTurn_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void DestroyMe();
	// Sets default values for this actor's properties
	AFloorTileCorner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	
	
};
