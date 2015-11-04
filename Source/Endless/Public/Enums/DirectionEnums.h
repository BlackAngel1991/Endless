// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "DirectionEnums.generated.h"
/**
 * 
 */
UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class EForwardDirection : uint8
{
	EC_X 	UMETA(DisplayName = "Fowrad is X"),
	EC_Y 	UMETA(DisplayName = "Forward is Y")

};

UENUM(BlueprintType)		//"BlueprintType" is essential to include
enum class ECornerType : uint8
{
	EC_Left 	UMETA(DisplayName = "To Left"),
	EC_Right 	UMETA(DisplayName = "To Right"),
	EC_None		UMETA(DisplayName = "No DIrection")

};
