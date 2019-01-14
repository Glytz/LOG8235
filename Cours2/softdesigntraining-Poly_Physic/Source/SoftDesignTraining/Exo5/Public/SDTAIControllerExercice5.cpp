// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SDTAIControllerExercice5.h"
#include "Exo5/Private/SDTProjectile.h"
#include "DrawDebugHelpers.h"
#include "Exo6/Private/PawnDataContainerComponent.h"
#include "Components/SplineComponent.h"
#include "PhysicsHelpers.h"

bool ASDTAIControllerExercice5::MoveToTarget(FVector2D target, float speed, float deltaTime)
{
	return false;
}

void ASDTAIControllerExercice5::MoveTowardsDirection(FVector2D direction, float speed, float deltaTime)
{
}

bool ASDTAIControllerExercice5::ReachSpline(USplineComponent const& spline, float deltaTime)
{
	return false;
}

bool ASDTAIControllerExercice5::FollowSpline(USplineComponent const& spline, float deltaTime)
{
	return false;
}

bool ASDTAIControllerExercice5::GetAroundObstacle(float deltaTime)
{
	return false;
}

float ASDTAIControllerExercice5::GetDistanceToSpline(USplineComponent const& spline)
{
	return 0.0f;
}

bool ASDTAIControllerExercice5::FollowSplineInDynamicObstacles(USplineComponent const& spline, float deltaTime)
{
	return false;
}

USplineComponent* ASDTAIControllerExercice5::GetClosestSplineWithoutObstacle(TArray<USplineComponent*> const & splines) const
{
	return nullptr;
}

FVector2D ASDTAIControllerExercice5::FindSplineClosestPosition(USplineComponent const& spline) const
{
	return FVector2D(0.0f, 0.0f);
}

TArray<FOverlapResult> ASDTAIControllerExercice5::CollectTargetActorsInFrontOfCharacter(APawn const* pawn, PhysicsHelpers& physicHelper) const
{
	return TArray<FOverlapResult>();
}