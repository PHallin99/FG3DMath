// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ContextTarget.h"
#include "FG3DMath/NarrowPhaseCollision.h"
#include "GameFramework/Actor.h"
#include "ContextSource.generated.h"

UCLASS()
class FG3DMATH_API AContextSource : public AActor {
	GENERATED_BODY()

	UPROPERTY(EditInstanceOnly)
	TArray<AContextTarget*> ContextTargets;

	FNarrowPhaseCollision* Collision;

public:
	AContextSource();
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;

	virtual void Tick(float DeltaTime) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
};
