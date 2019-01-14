// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Exo3WayPoint.h"

#include "Exo3LocationMovingBlock.generated.h"

UCLASS()
class SOFTDESIGNTRAINING_API AExo3LocationMovingBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExo3LocationMovingBlock();

protected:
    /// We keep those to have access during the NotifyHitEvent, we shouldn't do this, but it's simplier that way
    float SweepDeltaTime;
    float SweepSpeed;
    FVector SweepMovementDirection;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

    int CurrentWayPoint;

    bool SweepPhysic;

    virtual FVector GetNewFramePosition(FVector wayPointLocation, float speedToPoint, float DeltaTime);
    virtual FVector GetNewVelocity(FVector wayPointLocation, float speedToPoint, float DeltaTime);

    virtual FVector GetContactReactionMovement(FVector movementDirection, float movementSpeed, FVector HitLocation, FVector HitNormal);

    virtual void NotifyHit(class UPrimitiveComponent* MyComp, AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UPROPERTY(EditAnywhere)
    TArray<AExo3WayPoint*> WayPointList;

    UPROPERTY(EditAnywhere)
    bool UseVelocityMovement;

};
