// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include <cmath>
#include "Exo2PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/PhysicalMaterials/PhysicalMaterial.h"

#include "TargetActor.h"

int AExo2PlayerController::SURFACE_TYPE_WOOD = SurfaceType1;
int AExo2PlayerController::SURFACE_TYPE_METAL = SurfaceType2;
int AExo2PlayerController::SURFACE_TYPE_GLASS = SurfaceType3;

// Called every frame
void AExo2PlayerController::Tick(float DeltaTime)
{
    UWorld * World = GetWorld();
    PhysicsHelpers newPhysicHelper(World);
    FVector currentLocation = GetCharacter()->GetActorLocation();

	TArray<AActor*> resetActors;
	UGameplayStatics::GetAllActorsOfClass(World, ATargetActor::StaticClass(), resetActors);
	for (AActor* actor : resetActors)
	{
		((ATargetActor*)actor)->SetVisibilityInformation(false, false);
	}
	DrawCharacterAxes(World, GetPawn());
	DrawVisionCone(World, GetPawn(), GetPawn()->GetActorForwardVector(), m_visionAngle);
    TArray<FOverlapResult> foundActors = CollectTargetActorsInFrontOfCharacter(GetPawn(), newPhysicHelper);

	for (FOverlapResult overlapResult : foundActors)
    {
		if (ATargetActor* targetActor = dynamic_cast<ATargetActor*>(overlapResult.GetActor()))
		{
			if (IsInsideCone(GetPawn(), targetActor))
			{
				bool canSee = false;
				bool canShoot = false;
				GetVisibilityInformationForTarget(targetActor, currentLocation, newPhysicHelper, canSee, canShoot);
				targetActor->SetVisibilityInformation(canSee, canShoot);
			}
		}
    }
}

void AExo2PlayerController::GetVisibilityInformationForTarget(ATargetActor* targetActor, FVector selfPosition, PhysicsHelpers& physicHelper, bool& canSee, bool& canShoot)
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

void AExo2PlayerController::DrawCharacterAxes(UWorld* world, APawn* pawn) const
{
	FVector const pawnPosition = pawn->GetActorLocation();
	DrawDebugDirectionalArrow(world, pawnPosition, pawnPosition + pawn->GetActorRightVector() * 100.0f, 100, FColor::Green, false, -1.0f, 000, 5.0f);
	DrawDebugDirectionalArrow(world, pawnPosition, pawnPosition + pawn->GetActorForwardVector() * 100.0f, 100, FColor::Red, false, -1.0f, 000, 5.0f);
	DrawDebugDirectionalArrow(world, pawnPosition, pawnPosition + pawn->GetActorUpVector() * 100.0f, 100, FColor::Blue, false, -1.0f, 000, 5.0f);
}

void AExo2PlayerController::DrawVisionCone(UWorld* world, APawn* pawn, FVector const& dir, float angle) const
{
	DrawDebugCone(world, pawn->GetActorLocation(), dir, 5000.0f, angle, angle, 50, FColor::Green, false, -1.0f, 0, 5.0f);
}

TArray<FOverlapResult> AExo2PlayerController::CollectTargetActorsInFrontOfCharacter(APawn const* pawn, PhysicsHelpers& physicHelper) const
{
	TArray<FOverlapResult> outResults;
	physicHelper.SphereOverlap(pawn->GetActorLocation() + pawn->GetActorForwardVector() * 750.0f, 1000.0f, outResults, true);
	return outResults;
}

bool AExo2PlayerController::IsInsideCone(APawn * pawn, ATargetActor * targetActor) const
{
	FVector const toTarget = targetActor->GetActorLocation() - pawn->GetActorLocation();
	FVector const pawnForward = pawn->GetActorForwardVector();
	return std::abs(std::acos(FVector::DotProduct(pawnForward.GetSafeNormal(), toTarget.GetSafeNormal()))) < m_visionAngle;
}
