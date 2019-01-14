// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Exo3WayPoint.generated.h"

UCLASS()
class SOFTDESIGNTRAINING_API AExo3WayPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExo3WayPoint();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    // not visible, not shootable
    UPROPERTY(EditAnywhere)
    float TargetSpeed;
	
};
