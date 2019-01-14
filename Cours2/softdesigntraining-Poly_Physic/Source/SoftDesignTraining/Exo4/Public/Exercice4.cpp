// Fill out your copyright notice in the Description page of Project Settings.

#include "SoftDesignTraining.h"
#include "Exercice4.h"


///
/// Exercice 4
///
/// Votre objectif est de retourner un vecteur de movement pour permettre a l'objet de contourner
/// l'obstable.
///
/// movementDirection: Direction du mouvement avant d'avoir le contact
/// movementSpeed: Le déplacement de l'objet pour la trame
/// HitLocation: La position du contact
/// HitNormal: La normal de la surface du contact
///
FVector AExercice4::GetContactReactionMovement(FVector movementDirection, float movementSpeed, FVector HitLocation, FVector HitNormal)
{
    return FVector(0.0f, 0.0f, 0.0f);
}
