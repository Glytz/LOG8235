// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "Exercice1.h"

////
/// Exercice no 1: Vous devez être capable de déterminer si le ATargetActor est visible a partir le de la position
/// de votre character (selfPosition)
///
/// Vous devez utiliser les function utilitaire de PhysicHelper:
/// bool CastRay( const FVector& start,const FVector& end, TArray<struct FHitResult>& outHits, bool drawDebug );
///
/// Tous les objets touché par votre cast seront dans TArray<struct FHitResult> outHits
///
/// Vous pouvez utiliser le drawDebug pour visualiser le rayon
///
/// Vous retournez true si vous voyer le target actor a partir de la position, false s'il est obstrué
///
bool AExercice1::CheckForTargetVisibility(ATargetActor* targetActor, FVector selfPosition, PhysicsHelpers& physicHelper)
{
    return false;
}
