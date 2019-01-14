// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Exo4/Private/Exo4LocationMovingBlock.h"
#include "Exercice4.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API AExercice4 : public AExo4LocationMovingBlock
{
	GENERATED_BODY()
	
	
protected:
    virtual FVector GetContactReactionMovement(FVector movementDirection, float movementSpeed, FVector HitLocation, FVector HitNormal) override;
	
};
