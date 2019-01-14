// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SoftDesignTrainingPlayerController.h"
#include "PhysicsHelpers.h"
#include "TargetActor.h"

#include "Exo1PlayerController.generated.h"


/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API AExo1PlayerController : public ASoftDesignTrainingPlayerController
{
	GENERATED_BODY()
	
	
protected:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
	


    /// For Exo 1
    virtual bool CheckForTargetVisibility(ATargetActor* targetActor, FVector selfPosition, PhysicsHelpers& physicHelper);
};
