// Fill out your copyright notice in the Description page of Project Settings.

#include "Endless.h"
#include "EndlessCharacter.h"
#include "EndlessGameMode.h"
#include "FloorTileCorner.h"
#include "Components/ArrowComponent.h"

// Sets default values
AFloorTileCorner::AFloorTileCorner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	



	TrunTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TrunTrigger"));
	TrunTrigger->AttachParent = RootComponent;
	TrunTrigger->SetCollisionResponseToAllChannels(ECR_Ignore);
	TrunTrigger->SetCollisionResponseToChannel(ECC_Pawn, ECollisionResponse::ECR_Overlap);
	TrunTrigger->OnComponentBeginOverlap.AddDynamic(this, &AFloorTileCorner::onOverlapBeginTurn);
	TrunTrigger->OnComponentEndOverlap.AddDynamic(this, &AFloorTileCorner::onOverlapEndTurn);


	TileSpawnTrigger->SetBoxExtent(FVector(32, 32, 256));
	FloorSize = FVector(200, 200, 16);
	TrunTrigger->SetBoxExtent(FVector(200, 200, 200));
}

void AFloorTileCorner::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	//FVector ActorPos= AFloorTile::GetActorLocation();
	GBX = FloorSize.X;
	GBY = FloorSize.Y;
	GBZ = FloorSize.Z;
	Ground->SetRelativeLocation(FVector(0, -GBY, 0));
	TrunTrigger->SetRelativeLocation(FVector(GBX, 0, 0));
	UE_LOG(LogTemp, Warning, TEXT("Box %f,%f,%f"), GBX, GBY, GBZ);

	TileSpawnTrigger->SetBoxExtent(FVector(32, GBX, 256));
	if (CornerType == ECornerType::EC_Left)
	{
		Wall_1->SetRelativeRotation(FRotator(0, 0, 0));
		Wall_1->SetRelativeLocation(FVector(0, GBY, 0));
		Wall_2->SetRelativeRotation(FRotator(0, 90, 0));
		Wall_2->SetRelativeLocation(FVector(GBX * 2, -GBY, 0));

		if (!bCustomShape)
		{
			TileSpawnTrigger->SetRelativeRotation(FRotator(0, -90, 0));
			TileSpawnTrigger->SetRelativeLocation(FVector(GBX, -GBY, 256));
			SpawnPointArrow->SetRelativeRotation(FRotator(0, -90, 0));
			SpawnPointArrow->SetRelativeLocation(FVector(GBX, -GBY, 0));

		}
	}
	else
	{
		Wall_1->SetRelativeRotation(FRotator(0, -90, 0));
		Wall_2->SetRelativeRotation(FRotator(0, 0, 0));
		Wall_2->SetRelativeLocation(FVector(0, -GBY, 0));
		Wall_1->SetRelativeLocation(FVector(GBX * 2, GBY, 0));

		if (!bCustomShape)
		{
			TileSpawnTrigger->SetRelativeRotation(FRotator(0, 90, 0));
			TileSpawnTrigger->SetRelativeLocation(FVector(GBX, GBY, 256));

			SpawnPointArrow->SetRelativeRotation(FRotator(0, 90, 0));
			SpawnPointArrow->SetRelativeLocation(FVector(GBX, GBY, 0));

		}
	}
	NextSpawnPointRotaion = SpawnPointArrow->GetComponentRotation();
	NextSpawnPoint = SpawnPointArrow->GetComponentLocation();
}



void AFloorTileCorner::onOverlapBegin_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &HitRes)
{
	//UE_LOG(LogTemp, Warning, TEXT("Overlapp"));
	AEndlessGameMode* gm = Cast<AEndlessGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	AEndlessCharacter* character = Cast<AEndlessCharacter>(OtherActor);
	if (gm && character)
	{
		
		gm->AddFloorTile();
		GetWorld()->GetTimerManager().SetTimer(FuzeTimerHandle, this, &AFloorTileCorner::DestroyMe, 2, false);

	}
}
void AFloorTileCorner::onOverlapEnd_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("Overlapp End"));
}

/************************************************************************/
/* Trigger Corner Bool in CHaracter                                      */
/************************************************************************/
void AFloorTileCorner::onOverlapBeginTurn_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &HitRes)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapp Start"));
	AEndlessCharacter* Achar = Cast<AEndlessCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if ( Achar)
	{
		Achar->NextCenterLane = NextSpawnPoint;
		Achar->CornerDirection = CornerType;
		Achar->bCanTurn = true;
	}

}
void AFloorTileCorner::onOverlapEndTurn_Implementation(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Overlapp End"));
	AEndlessCharacter* Achar = Cast<AEndlessCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	if (Achar)
	{
		Achar->bCanTurn = false;
	}
}



// Called when the game starts or when spawned
void AFloorTileCorner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloorTileCorner::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AFloorTileCorner::DestroyMe()
{
	GetWorld()->GetTimerManager().ClearTimer(FuzeTimerHandle);
	this->Destroy();
}
