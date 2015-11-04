// Fill out your copyright notice in the Description page of Project Settings.

#include "Endless.h"
#include "RoadTiles/FloorTile.h"
#include "Player/EndlessCharacter.h"
#include "EndlessGameMode.h"
#include "Components/ArrowComponent.h"

// Sets default values
AFloorTile::AFloorTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
}


void AFloorTile::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
	
	//FVector ActorPos= AFloorTile::GetActorLocation();
	GBX = FloorSize.X;
	GBY = FloorSize.Y;
	GBZ = FloorSize.Z;
	Ground->SetRelativeLocation(FVector(0, -GBY, 0));
	UE_LOG(LogTemp, Warning, TEXT("Box %f,%f,%f"), GBX,GBY,GBZ);

		TileSpawnTrigger->SetBoxExtent(FVector(32, GBY, 256));
		if (!bCustomShape)
		{
			TileSpawnTrigger->SetRelativeLocation(FVector(GBX * 2 - 16, 0, 256));
			SpawnPointArrow->SetRelativeLocation(FVector(GBX * 2, 0, 0));
		}

	NextSpawnPointRotaion = SpawnPointArrow->GetComponentRotation();
	NextSpawnPoint = SpawnPointArrow->GetComponentLocation();


}

void AFloorTile::onOverlapBegin_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &HitRes)
{
	//UE_LOG(LogTemp, Warning, TEXT("Overlapp"));
	AEndlessGameMode* gm = Cast<AEndlessGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	AEndlessCharacter* character = Cast<AEndlessCharacter>(OtherActor);
	if (gm && character)
	{

		gm->AddFloorTile();
		GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AFloorTile::DestroyMe, 2, false);
		
	}
}
void AFloorTile::onOverlapEnd_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("Overlapp End"));
}


// Called when the game starts or when spawned
void AFloorTile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloorTile::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AFloorTile::DestroyMe()
{
	GetWorld()->GetTimerManager().ClearTimer(FuzeTimerHandle);
	this->Destroy();
}