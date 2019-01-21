// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "SDTAIControllerExercice5.h"
#include "Exo5/Private/SDTProjectile.h"
#include "DrawDebugHelpers.h"
#include "Exo6/Private/PawnDataContainerComponent.h"
#include "Components/SplineComponent.h"
#include "PhysicsHelpers.h"

bool ASDTAIControllerExercice5::MoveToTarget(FVector2D target, float targetSpeed, float deltaTime)
{
	APawn* pawn = GetPawn();
	FVector const pawnPosition(pawn->GetActorLocation());
	FVector2D const toTarget = target - FVector2D(pawnPosition);
	FVector2D const displacement = FMath::Min(toTarget.Size(), FMath::Min(m_maxSpeed, targetSpeed) * deltaTime) * toTarget.GetSafeNormal();
	pawn->SetActorLocation(pawnPosition + FVector(displacement, 0.f), true);
	pawn->SetActorRotation(FVector(displacement, 0.f).ToOrientationQuat());
	return toTarget.Size() < FMath::Min(m_maxSpeed, targetSpeed) * deltaTime;
}

void ASDTAIControllerExercice5::MoveTowardsDirection(FVector2D direction, float targetSpeed, float deltaTime)
{
	APawn* pawn = GetPawn();
	FVector const pawnPosition(pawn->GetActorLocation());
	FVector2D const displacement = FMath::Min(m_maxSpeed, targetSpeed) * deltaTime * direction.GetSafeNormal();
	pawn->SetActorLocation(pawnPosition + FVector(displacement, 0.f), true);
	pawn->SetActorRotation(FVector(direction, 0.f).ToOrientationQuat());
}

bool ASDTAIControllerExercice5::ReachSpline(USplineComponent const& spline, float deltaTime)
{
	return MoveToTarget(FindSplineClosestPosition(spline), this->m_maxSpeed, deltaTime);
}

bool ASDTAIControllerExercice5::FollowSpline(USplineComponent const& spline, float deltaTime)
{
	FVector const actorPosition(GetPawn()->GetActorLocation());
	FVector const direction = spline.FindDirectionClosestToWorldLocation(actorPosition, ESplineCoordinateSpace::World);
	MoveTowardsDirection(FVector2D(direction), m_maxSpeed, deltaTime);

	return (spline.FindInputKeyClosestToWorldLocation(GetPawn()->GetActorLocation()) / spline.GetNumberOfSplinePoints() - 1) > 0.99f;
}

bool ASDTAIControllerExercice5::GetAroundObstacle(float deltaTime)
{
	if (m_hitInformation.HandleHit())
	{
		FVector2D const contactDirection = FVector2D(FVector::CrossProduct(FVector::UpVector, FVector(m_hitInformation.m_hitNormal, 0.0f)));
		MoveTowardsDirection(contactDirection, m_maxSpeed, deltaTime);
		return false;
	}
	return true;
}

float ASDTAIControllerExercice5::GetDistanceToSpline(USplineComponent const& spline)
{
	FVector2D const position(GetPawn()->GetActorLocation());
	return abs(FVector2D::Distance(position, FindSplineClosestPosition(spline)));
}

bool ASDTAIControllerExercice5::FollowSplineInDynamicObstacles(USplineComponent const& spline, float deltaTime)
{
	PhysicsHelpers physicsHelper = PhysicsHelpers(GetWorld());
	float newSpeed = this->m_maxSpeed;
	FVector const actorPosition(GetPawn()->GetActorLocation());
	FVector const direction = spline.FindDirectionClosestToWorldLocation(actorPosition, ESplineCoordinateSpace::World);
	FVector2D newDirection = FVector2D(direction*newSpeed);
	bool noCollision = false;
	float minColTime = MAX_flt;
	for (CollisionInfo collision : this->RecoverIncomingCollisions(newDirection))
	{
		/*if (collision.m_timeToCollision < minColTime)
		{
			minColTime = collision.m_timeToCollision;
			closestCollision = collision;
		}*/
		if (collision.m_timeToCollision < 0.5f)
		{
			newSpeed = 0.f;
		}
	}
	MoveTowardsDirection(newDirection, newSpeed, deltaTime);
	return (spline.FindInputKeyClosestToWorldLocation(GetPawn()->GetActorLocation()) / (spline.GetNumberOfSplinePoints() - 1)) > 0.99f;
}

USplineComponent* ASDTAIControllerExercice5::GetClosestSplineWithoutObstacle(TArray<USplineComponent*> const & splines)
{
	FVector2D const position(GetPawn()->GetActorLocation());
	float minDistance = MAX_flt;
	USplineComponent *splineToReturn = nullptr;
	for (USplineComponent *spline : splines)
	{
		PhysicsHelpers physicsHelper = PhysicsHelpers(GetWorld());
		TArray<struct FHitResult> outHits;
		FVector pos3D = GetPawn()->GetActorLocation();
		if (!physicsHelper.CastRay(FVector(position, 100.f), FVector(FindSplineClosestPosition(*spline), 100.f), outHits, true))
		{
			float distance = GetDistanceToSpline(*spline);
			if (minDistance > distance)
			{
				minDistance = distance;
				splineToReturn = spline;
			}
		}
	}
	return splineToReturn;
}

FVector2D ASDTAIControllerExercice5::FindSplineClosestPosition(USplineComponent const& spline) const
{
	FVector2D const actorPosition(GetPawn()->GetActorLocation());
	return FVector2D(spline.FindLocationClosestToWorldLocation(FVector(actorPosition,0.0f), ESplineCoordinateSpace::World));
}

TArray<FOverlapResult> ASDTAIControllerExercice5::CollectTargetActorsInFrontOfCharacter(APawn const* pawn, PhysicsHelpers& physicHelper) const
{
	return TArray<FOverlapResult>();
}