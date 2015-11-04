// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "BaseRoadTile.generated.h"

UCLASS()
class ENDLESS_API ABaseRoadTile : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Meshes")
	class USceneComponent* scene;

	/************************************************************************/
	/*                               vars                                   */
	/************************************************************************/
	/* Handle to manage the timer */
	FTimerHandle FuzeTimerHandle;

	float GBX;
	float GBY;
	float GBZ;

	//Size of Floor in half of Width,Long,Height
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "defaults")
		FVector FloorSize;


	//Set to TRUE if u want position Meshes Manually
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "defaults")
		bool bCustomShape;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "defaults")
		FVector NextSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "defaults")
		FRotator NextSpawnPointRotaion;


	/************************************************************************/
	/*                             Meshes                                   */
	/************************************************************************/

	//Floor Mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Meshes")
	class UStaticMeshComponent* Ground;
	//Wall mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Meshes")
	class UStaticMeshComponent* Wall_1;
	//Wall mesh
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Meshes")
	class UStaticMeshComponent* Wall_2;



	/************************************************************************/
	/*                          Triggers                                    */
	/************************************************************************/
	//Spawn & Destroy Trigger
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Meshes")
	class UBoxComponent* TileSpawnTrigger;

	/************************************************************************/
	/*                         Arrow Components                              */
	/************************************************************************/

	//Position of Next SpawnPoint
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "defaults")
	class UArrowComponent* SpawnPointArrow;


public:	
	// Sets default values for this actor's properties
	ABaseRoadTile();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintNativeEvent, Category = "Spawn and Destroy")
		void onOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &HitRes);
	virtual void onOverlapBegin_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
		bool bFromSweep, const FHitResult &HitRes);


	UFUNCTION(BlueprintNativeEvent, Category = "Spawn and Destroy")
		void onOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	virtual void onOverlapEnd_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


	
	
};
