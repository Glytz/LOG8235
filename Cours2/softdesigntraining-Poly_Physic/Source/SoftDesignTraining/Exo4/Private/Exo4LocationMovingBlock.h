// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Exo3/Private/Exo3LocationMovingBlock.h"
#include "Exo4LocationMovingBlock.generated.h"

/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API AExo4LocationMovingBlock : public AExo3LocationMovingBlock
{
	GENERATED_BODY()
	
public:
    // Sets default values for this actor's properties
    AExo4LocationMovingBlock();
	
public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
    virtual FVector GetContactReactionMovement(FVector movementDirection, float movementSpeed, FVector HitLocation, FVector HitNormal) override;
	
};
