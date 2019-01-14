// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "Exo3LocationMovingBlock.h"


// Sets default values
AExo3LocationMovingBlock::AExo3LocationMovingBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CurrentWayPoint = 0;

    UseVelocityMovement = false;
    SweepPhysic = false;

    SweepDeltaTime = 0.0f;
    SweepSpeed = 0.0f;
    SweepMovementDirection = FVector(0.0f, 0.0f, 0.0f);
}

// Called when the game starts or when spawned
void AExo3LocationMovingBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

void AExo3LocationMovingBlock::NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
    FVector correctionMovement = GetContactReactionMovement(SweepMovementDirection, SweepSpeed, HitLocation, HitNormal);
    FVector finalLocation = GetActorLocation() + correctionMovement;

    SetActorLocation(finalLocation, SweepPhysic);
}

// Called every frame
void AExo3LocationMovingBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (WayPointList.Num() == 0)
    {
        return;
    }

    AExo3WayPoint* currentWayPoint = WayPointList[CurrentWayPoint];

    FVector finalLocation;
    FVector targetLocation = currentWayPoint->GetActorLocation();
    FVector currentLocation = GetActorLocation();

    if (UseVelocityMovement)
    {
        FVector velocity = GetNewVelocity(targetLocation, currentWayPoint->TargetSpeed, DeltaTime);

        finalLocation = currentLocation + velocity * DeltaTime;
    }
    else
    {
        finalLocation = GetNewFramePosition(targetLocation, currentWayPoint->TargetSpeed, DeltaTime);
    }

    SweepDeltaTime = DeltaTime;
    SweepMovementDirection = (finalLocation - currentLocation);
    SweepSpeed = SweepMovementDirection.Size();
    SweepMovementDirection.Normalize();

    SetActorLocation(finalLocation, SweepPhysic);

    if ( targetLocation.Equals(finalLocation) )
    {
        CurrentWayPoint = CurrentWayPoint + 1;

        if (CurrentWayPoint >= WayPointList.Num())
        {
            CurrentWayPoint = 0;
        }
    }
}

FVector AExo3LocationMovingBlock::GetContactReactionMovement(FVector movementDirection, float movementSpeed, FVector HitLocation, FVector HitNormal)
{
    return FVector();
}

FVector AExo3LocationMovingBlock::GetNewVelocity(FVector wayPointLocation, float speedToPoint, float DeltaTime)
{
    FVector currentLocation = GetActorLocation();
    FVector toTarget = wayPointLocation - currentLocation;
    float distanceLeft = toTarget.Size();
    toTarget.Normalize();

    // Il faut s'assurer de ne pas dépasser la position du waypoint
    float movementThisFrame = speedToPoint * DeltaTime;

    if (movementThisFrame > distanceLeft)
    {
        float ratio = distanceLeft / movementThisFrame;

        return toTarget * speedToPoint * ratio;
    }

    return toTarget * speedToPoint;
}

FVector AExo3LocationMovingBlock::GetNewFramePosition(FVector wayPointLocation, float speedToPoint, float DeltaTime)
{
    FVector currentLocation = GetActorLocation();

    FVector finalLocation = FMath::VInterpConstantTo(currentLocation, wayPointLocation, DeltaTime, speedToPoint);

    return finalLocation;
}
