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
	
	//Input for changing Direction to Left or Right <Coreners in Road>
	InputComponent->BindAction("TurnRight", IE_Pressed, this, &AEndlessCharacter::TurnRight);
	InputComponent->BindAction("TurnLeft", IE_Pressed, this, &AEndlessCharacter::TurnLeft);

	
	InputComponent->BindAxis("MoveForward", this, &AEndlessCharacter::MoveForward);

	//Using it for changing lanes smoothly
	InputComponent->BindAxis("MoveRight", this, &AEndlessCharacter::MoveRight);

	//Setting Current Forward Axis
	//Sins we only rotate character 90 degree we 
	//dont need complex math to detect right direction;
	CurrentForward = EForwardDirection::EC_X;

}


void AEndlessCharacter::TurnRight()
{
	//Check if bCanTurn has been set to true by FloorTileCorner to init character rotaion
	if (bCanTurn)
	{
		UE_LOG(LogTemp, Warning, TEXT("TurnRight"));
		InputDirection = ECornerType::EC_Right;

		//if the direction of Corner and Input is not same set bCanTurn to false and exit function
		if (InputDirection != CornerDirection)
		{
			bCanTurn = false;
			return;
		}
		//else set CenterLane to NextCenterLane  and add 90 degree
		//to DesiredRotation for rotating character +90 degree
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

	//get Current Rotation
	const FRotator Rotation = Controller->GetControlRotation();
	
	
	
		//check that current rotation and DesierdRotaion are equal or not
		//if they are not then use RInterpTo to rate charater at given speed
		if (!Rotation.Equals(DesierdRotaion, 0.1))
		{

			FRotator C = FMath::RInterpTo(Rotation, DesierdRotaion, this->GetWorld()->GetDeltaSeconds(), RotationSpeed);
			Controller->SetControlRotation(C);


		}
		//if character can turn  and player used turn input set current rotation to desired rotation
		//the reason we r checking is that this function running every tick and we don't want to call 
		//DirectonSwap  every tick (if we call it inside TurnLeft or TurnRight weird thing will happen
		//and the reason why we r setting Rotation after RInterpTo is that RInterpTo will never Set 
		//rotation to exact 90,180,270,... it will always left result with some float value like 89.8, 179.4,...
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
		//will use it for FInterpTo
		float TempLoc = 0.f;
		//TempLoc = Value;
		//if CurrentForward is X then we should Add offset to Y Axis to position of character
		//else we should add it to X position
		switch (CurrentForward)
		{

		case EForwardDirection::EC_X:
			//calculate the position that character should go to change lane (only on Axis)
			TempLoc = CenterLane.Y + (LaneOffset.Y*Value*GetActorRightVector().Y);
			//UE_LOG(LogTemp, Error, TEXT("X Axis & Pos: %s ,%f"), *ActorPosition.ToString(), TempLoc);
			//Only Set Y axis of character position so we wont interrupt character forward movement or jump or slide 
			NextPosition = FVector(ActorPosition.X,
				FMath::FInterpTo(ActorPosition.Y, TempLoc, _DeltaTime, LaneChangeSpeed),
				ActorPosition.Z);
			break;
		case EForwardDirection::EC_Y:
			
			TempLoc = CenterLane.X + (LaneOffset.X*Value*GetActorRightVector().X);

			//UE_LOG(LogTemp, Error, TEXT("Y Axis & Pos: %s ,%f"), *ActorPosition.ToString(), TempLoc);
			//Only Set X axis of character position so we wont interrupt character forward movement or jump or slide
			NextPosition = FVector(FMath::FInterpTo(ActorPosition.X, TempLoc, _DeltaTime, LaneChangeSpeed),
				ActorPosition.Y,
				ActorPosition.Z);
			break;
		}

		//and finally set character position <function is running every frame so everything will work smoothly>
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
