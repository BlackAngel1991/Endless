// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/Character.h"
#include "Enums/DirectionEnums.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
		bool bCanTurn;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Bools)
		FRotator DesierdRotaion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "defaults")
		FVector LaneOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "defaults")
		FVector CenterLane;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "defaults")
		FVector NextCenterLane;

	UPROPERTY()
		EForwardDirection CurrentForward;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "defaults")
		float LaneChangeSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "defaults")
		float forwardSpeedScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "defaults")
		float RotationSpeed;

	ECornerType CornerDirection;
	ECornerType InputDirection;


private:
	bool isTurned;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);


	void TurnRight();
	void TurnLeft();

	void TurnCorner();

	void DirectonSwap();
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	// End of APawn interface

public:
	float _DeltaTime;
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;
};

