// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "Exo4LocationMovingBlock.h"

// Sets default values
AExo4LocationMovingBlock::AExo4LocationMovingBlock()
{
    SweepPhysic = true;
}

// Called every frame
void AExo4LocationMovingBlock::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

FVector AExo4LocationMovingBlock::GetContactReactionMovement(FVector movementDirection, float movementSpeed, FVector HitLocation, FVector HitNormal)
{
    FVector movementCorrection = FVector(0.0f, 0.0f, 0.0f);

    float dotProduct = FVector::DotProduct(movementDirection, -HitNormal);
    float angle = FMath::Acos(dotProduct);

    if (angle <= 0.2f)
    {
        FVector contactPlane = FVector::CrossProduct(HitNormal, FVector::UpVector );
        movementCorrection = contactPlane * movementSpeed;
    }
    else
    {
        FVector contactUpVec = FVector::CrossProduct(HitNormal, movementDirection);
        FVector contactPlaneMovement = FVector::CrossProduct(contactUpVec, HitNormal);

        movementCorrection = contactPlaneMovement * movementSpeed;
    }

    return movementCorrection;
}