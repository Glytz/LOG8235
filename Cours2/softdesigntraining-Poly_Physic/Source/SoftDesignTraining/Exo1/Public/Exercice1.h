// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Exo1/Exo1PlayerController.h"
#include "PhysicsHelpers.h"
#include "TargetActor.h"

#include "Exercice1.generated.h"


/**
 * 
 */
UCLASS()
class SOFTDESIGNTRAINING_API AExercice1 : public AExo1PlayerController
{
	GENERATED_BODY()
	
	
public:
    virtual bool CheckForTargetVisibility(ATargetActor* targetActor, FVector selfPosition, PhysicsHelpers& physicHelper) override;
};
