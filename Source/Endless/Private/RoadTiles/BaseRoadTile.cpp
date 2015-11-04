// Fill out your copyright notice in the Description page of Project Settings.

#include "Endless.h"
#include "Components/ArrowComponent.h"
#include "BaseRoadTile.h"


// Sets default values
ABaseRoadTile::ABaseRoadTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	RootComponent = scene;
	Ground = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GroundMesh"));
	Ground->AttachParent = RootComponent;
	Wall_1 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMeshRight"));
	Wall_1->AttachParent = RootComponent;
	Wall_2 = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WallMeshLeft"));
	Wall_2->AttachParent = RootComponent;

	TileSpawnTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TileSpawnTriger"));
	TileSpawnTrigger->AttachParent = RootComponent;
	TileSpawnTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	TileSpawnTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TileSpawnTrigger->OnComponentBeginOverlap.AddDynamic(this, &ABaseRoadTile::onOverlapBegin);
	TileSpawnTrigger->OnComponentEndOverlap.AddDynamic(this, &ABaseRoadTile::onOverlapEnd);

	SpawnPointArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnTrigger"));
	SpawnPointArrow->AttachParent = RootComponent;
	TileSpawnTrigger->SetBoxExtent(FVector(32, 32, 256));
	FloorSize = FVector(200, 200, 16);
}

// Called when the game starts or when spawned
void ABaseRoadTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseRoadTile::Tick(float DeltaTime)
{
	Super::Tick( DeltaTime );

}

void ABaseRoadTile::onOverlapBegin_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &HitRes)
{

}
void ABaseRoadTile::onOverlapEnd_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("Overlapp End"));
}

