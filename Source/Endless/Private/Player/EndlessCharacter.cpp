// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "Endless.h"
#include "EndlessCharacter.h"

//////////////////////////////////////////////////////////////////////////
// AEndlessCharacter

AEndlessCharacter::AEndlessCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
	DesierdRotaion = FRotator(0, 0, 0);
	RotationSpeed = 30;
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;
	bCanTurn = false;
	InputDirection = ECornerType::EC_None;
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = false; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 1080.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->AttachTo(RootComponent);
	CameraBoom->TargetArmLength = 300.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->AttachTo(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)
}

//////////////////////////////////////////////////////////////////////////
// Input

void AEndlessCharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	// Set up gameplay key bindings
	check(InputComponent);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	InputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	InputComponent->BindAction("TurnRight", IE_Pressed, this, &AEndlessCharacter::TurnRight);
	InputComponent->BindAction("TurnLeft", IE_Pressed, this, &AEndlessCharacter::TurnLeft);

	InputComponent->BindAxis("MoveForward", this, &AEndlessCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AEndlessCharacter::MoveRight);

	CurrentForward = EForwardDirection::EC_X;

}


void AEndlessCharacter::TurnRight()
{
	if (bCanTurn)
	{
		UE_LOG(LogTemp, Warning, TEXT("TurnRight"));
		InputDirection = ECornerType::EC_Right;
		if (InputDirection != CornerDirection)
		{
			bCanTurn = false;
			return;
		}
		CenterLane = NextCenterLane;
		isTurned = true;
		DesierdRotaion.Yaw += 90;
		

	}

}
void AEndlessCharacter::TurnLeft()
{
	if (bCanTurn)
	{
		UE_LOG(LogTemp, Warning, TEXT("TurnLeft"));
		InputDirection = ECornerType::EC_Left;
		if (InputDirection != CornerDirection)
		{
			bCanTurn = false;
			return;
		}
		CenterLane = NextCenterLane;
		isTurned = true;
		DesierdRotaion.Yaw -= 90;
		
	}

}
void AEndlessCharacter::DirectonSwap()
{
	if (CurrentForward == EForwardDirection::EC_X)
	{
		CurrentForward = EForwardDirection::EC_Y;
	} 
	else
	{
		CurrentForward = EForwardDirection::EC_X;
	}
}
void AEndlessCharacter::TurnCorner()
{
	const FRotator Rotation = Controller->GetControlRotation();
	
	
	
		
		if (!Rotation.Equals(DesierdRotaion, 0.1))
		{

			FRotator C = FMath::RInterpTo(Rotation, DesierdRotaion, this->GetWorld()->GetDeltaSeconds(), RotationSpeed);
			Controller->SetControlRotation(C);


		}
		else if (isTurned)
		{

			AEndlessCharacter::DirectonSwap();
			Controller->SetControlRotation(DesierdRotaion);
			isTurned = false;

		}
	
	
	/*	UE_LOG(LogTemp, Warning, TEXT("CR: %f , %f , %f and DR %f , %f , %f"), Rotation.Yaw, Rotation.Pitch, Rotation.Roll,
	DesierdRotaion.Yaw, DesierdRotaion.Pitch, DesierdRotaion.Roll);*/
	
}



void AEndlessCharacter::MoveForward(float Value)
{
	if ((Controller != NULL))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, forwardSpeedScale);
	}
}

void AEndlessCharacter::MoveRight(float Value)
{
	if ( (Controller != NULL))
	{

		FVector ActorPosition = GetActorLocation();
		FVector NextPosition = FVector(0, 0, 0);
		float TempLoc = 0.f;
		//TempLoc = Value;
		switch (CurrentForward)
		{
		case EForwardDirection::EC_X:
			
			TempLoc = CenterLane.Y + (LaneOffset.Y*Value*GetActorRightVector().Y);
			UE_LOG(LogTemp, Error, TEXT("X Axis & Pos: %s ,%f"), *ActorPosition.ToString(), TempLoc);
			NextPosition = FVector(ActorPosition.X,
				FMath::FInterpTo(ActorPosition.Y, TempLoc, _DeltaTime, LaneChangeSpeed),
				ActorPosition.Z);
			break;
		case EForwardDirection::EC_Y:
			
			TempLoc = CenterLane.X + (LaneOffset.X*Value*GetActorRightVector().X);
			UE_LOG(LogTemp, Error, TEXT("Y Axis & Pos: %s ,%f"), *ActorPosition.ToString(), TempLoc);
			NextPosition = FVector(FMath::FInterpTo(ActorPosition.X, TempLoc, _DeltaTime, LaneChangeSpeed),
				ActorPosition.Y,
				ActorPosition.Z);
			break;
		}
		SetActorRelativeLocation(NextPosition);

		////// find out which way is right
		//const FRotator Rotation = Controller->GetControlRotation();
		//const FRotator YawRotation(0, Rotation.Yaw, 0);
	
		////// get right vector 
		//const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		////// add movement in that direction
		//AddMovementInput(Direction, Value);
	}
}
void AEndlessCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	_DeltaTime = DeltaTime;
	AEndlessCharacter::TurnCorner();
}
