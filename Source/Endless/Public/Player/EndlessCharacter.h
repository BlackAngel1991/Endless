// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Enums/EndlessEnums.h"
#include "EndlessCharacter.generated.h"

UCLASS(config=Game)
class AEndlessCharacter : public ACharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;


public:
	AEndlessCharacter(const FObjectInitializer& ObjectInitializer);

	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseTurnRate;

	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
	float BaseLookUpRate;

	//this bool will be set by Corner Tiles so the character can rotate to left or right
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
		bool bCanTurn;

	//the rotation that character should rotate :/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
		FRotator DesierdRotaion;

	//how far character will go left or right
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "defaults")
		FVector LaneOffset;
	//the center lane position
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "defaults")
		FVector CenterLane;

	//Store next center lane position to setting it after character rotate in corners
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "defaults")
		FVector NextCenterLane;

	//Current Forward Axis
	UPROPERTY()
		EForwardDirection CurrentForward;
	//How fast character change lanes
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "defaults")
		float LaneChangeSpeed;
	//how fast character run
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "defaults")
		float forwardSpeedScale;
	//how fast character rotate
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "defaults")
		float RotationSpeed;

	//will set by corner tile to now the right direction
	ECornerType CornerDirection;

	//the direction that player given
	ECornerType InputDirection;


private:

	//Set true when the character start turning
	bool isTurned;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	//Rotate to Right
	void TurnRight();

	//Rotate to Left
	void TurnLeft();

	//Function that will run every tick to rotate character when needed
	void TurnCorner();

	//FlipFlop to change CurrentForward
	void DirectonSwap();

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:

	//Holding DeltaSecond
	float _DeltaTime;
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
};

