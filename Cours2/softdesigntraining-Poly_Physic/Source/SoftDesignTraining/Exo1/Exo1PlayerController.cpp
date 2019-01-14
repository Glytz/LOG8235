// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "Exo1PlayerController.h"

#include "PhysicsHelpers.h"
#include "TargetActor.h"

// Called every frame
void AExo1PlayerController::Tick(float DeltaTime)
{
    UWorld * World = GetWorld();
    PhysicsHelpers newPhysicHelper(World);

    FVector currentLocation = GetCharacter()->GetActorLocation();

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(World, ATargetActor::StaticClass(), FoundActors);

    for ( int i = 0; i < FoundActors.Num(); ++i)
    {
        ATargetActor* targetActor = (ATargetActor*)FoundActors[i];

        targetActor->SetVisibilityInformation( CheckForTargetVisibility(targetActor, currentLocation, newPhysicHelper), true );
    }
}

bool AExo1PlayerController::CheckForTargetVisibility(ATargetActor* targetActor, FVector selfPosition, PhysicsHelpers& physicHelper)
{
    TArray<struct FHitResult> hitResult;
    physicHelper.CastRay(selfPosition, targetActor->GetActorLocation(), hitResult, true);

    bool isVisible = true;
    for (int j = 0; j < hitResult.Num(); ++j)
    {
        if (hitResult[j].GetActor() != targetActor)
        {
            isVisible = false;
        }
    }

    return isVisible;
}

