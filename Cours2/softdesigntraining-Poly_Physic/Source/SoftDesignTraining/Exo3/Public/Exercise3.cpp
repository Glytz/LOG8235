// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "Exercise3.h"


///
/// Exercice 3
///
/// Vous devez calculer la nouvelle position pour chaque trame, en fonction de la position
/// du way point. Vous retournez la nouvelle position.
///
FVector AExercise3::GetNewFramePosition(FVector wayPointLocation, float speedToPoint, float DeltaTime)
{
    return GetActorLocation();
}

///
/// Exercice 3
///
/// Vous devez calculer la vélocité pour déplacer la boite à la bonne vitesse vers
/// le waypoint
///
FVector AExercise3::GetNewVelocity(FVector wayPointLocation, float speedToPoint, float DeltaTime)
{
    return FVector(0.0f, 0.0f, 0.0f);
}