// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Exo3/Private/Exo3LocationMovingBlock.h"
#include "Exercise3.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API AExercise3 : public AExo3LocationMovingBlock
{
	GENERATED_BODY()
	
	
protected:
    virtual FVector GetNewFramePosition(FVector wayPointLocation, float speedToPoint, float DeltaTime) override;

    virtual FVector GetNewVelocity(FVector wayPointLocation, float speedToPoint, float DeltaTime) override;

};
