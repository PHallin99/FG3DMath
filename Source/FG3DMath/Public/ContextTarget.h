// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FG3DMath/AABBData.h"
#include "FG3DMath/Interpolation.h"
#include "GameFramework/Actor.h"
#include "Materials/Material.h"
#include "ContextTarget.generated.h"

UCLASS()
class FG3DMATH_API AContextTarget : public AActor {
	GENERATED_BODY()

	UPROPERTY(VisibleInstanceOnly)
	TArray<FVector> TargetPositions;

	UPROPERTY()
	int PositionIndex;
	UPROPERTY()
	bool ShouldWait = true;
	UPROPERTY()
	float WaitDuration;
	UPROPERTY()
	float WaitTime = 0.f;
	UPROPERTY()
	FVector TargetPosition;
	UPROPERTY()
	FVector StartPosition;

	FInterpolation* Interpolation;

public:
	// Sets default values for this actor's properties
	AContextTarget();
	void SetMaterial(UMaterial* Material) const;
	void UpdateAABBData() const;
	FAABBData* AABBData;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* MeshComponent;
	UPROPERTY(EditDefaultsOnly)
	UMaterial* GreenMat;
	UPROPERTY(EditDefaultsOnly)
	UMaterial* YellowMat;
	UPROPERTY(EditDefaultsOnly)
	UMaterial* RedMat;
	UPROPERTY(EditDefaultsOnly)
	UMaterial* PurpleCollisionMat;

	virtual void Tick(float DeltaSeconds) override;
	virtual bool ShouldTickIfViewportsOnly() const override;
	
	void UpdateContext(const FVector& SourcePosition) const;
	void Interpolate(float DeltaTime) const;
};
