// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "Exercice2.h"
#include <cmath>
#include "DrawDebugHelpers.h"
#include "TargetActor.h"
#include "Runtime/Engine/Classes/PhysicalMaterials/PhysicalMaterial.h"

void AExercice2::GetVisibilityInformationForTarget(ATargetActor* targetActor, FVector selfPosition, PhysicsHelpers& physicHelper, bool& canSee, bool& canShoot)
{
	TArray<struct FHitResult> hitResult;
	physicHelper.CastRay(selfPosition, targetActor->GetActorLocation(), hitResult, true);

	canSee = true;
	canShoot = true;
	for (int j = 0; j < hitResult.Num(); ++j)
	{
		if (hitResult[j].GetActor() != targetActor)
		{
			UPhysicalMaterial* PhysicsMtl = hitResult[j].PhysMaterial.Get();
			if (PhysicsMtl != nullptr)
			{
				if (PhysicsMtl->SurfaceType == SURFACE_TYPE_WOOD)
				{
					canSee = false;
				}
				else if (PhysicsMtl->SurfaceType == SURFACE_TYPE_GLASS)
				{
					canShoot = false;
				}
				else
				{
					canSee = false;
					canShoot = false;
				}
			}
		}
	}
}

void AExercice2::DrawCharacterAxes(UWorld * world, APawn * pawn) const
{
	FTransform trans = pawn->GetActorTransform();
	FVector pawnPosition = pawn->GetActorLocation();
	FVector x = trans.GetUnitAxis(EAxis::X);
	FVector y = trans.GetUnitAxis(EAxis::Y);
	FVector z = trans.GetUnitAxis(EAxis::Z);
	DrawDebugDirectionalArrow(world, pawnPosition, pawnPosition + z * 100,10.f,FColor::Blue);
	DrawDebugDirectionalArrow(world, pawnPosition, pawnPosition + y * 100, 10.f, FColor::Green);
	DrawDebugDirectionalArrow(world, pawnPosition, pawnPosition + x * 100, 10.f, FColor::Red);
}

void AExercice2::DrawVisionCone(UWorld * world, APawn * pawn, FVector const & dir, float angle) const
{
	FVector playerLocation = pawn->GetActorLocation();
	int radius = 1000;
	FVector forwadVector = pawn->GetActorForwardVector();//pawn->GetActorTransform().GetUnitAxis(EAxis::X);
	DrawDebugCone(world, playerLocation, forwadVector, radius, this->m_visionAngle, this->m_visionAngle, 50, FColor::White,false, -1.0F,0,5.0F);
	DrawDebugLine(world, playerLocation, playerLocation + forwadVector*radius, FColor::Yellow);
}

TArray<FOverlapResult> AExercice2::CollectTargetActorsInFrontOfCharacter(APawn const * pawn, PhysicsHelpers & physicHelper) const
{
	//UWorld* world = pawn->GetWorld();
	FVector pawnPosition = pawn->GetActorLocation();
	FVector forwardVector = pawn->GetActorForwardVector();
	int radius = 500;
	TArray<FOverlapResult> outOverlaps;
	physicHelper.SphereOverlap(pawnPosition + forwardVector * radius, radius, outOverlaps, true);
	return outOverlaps;
}

bool AExercice2::IsInsideCone(APawn * pawn, ATargetActor * targetActor) const
{
	FVector dir = (targetActor->GetActorLocation() - pawn->GetActorLocation());
	dir.Normalize();
	float cosAngle = FVector::DotProduct(dir,pawn->GetActorForwardVector());
	return cosAngle > cos(this->m_visionAngle);
}
