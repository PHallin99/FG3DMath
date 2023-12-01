// Fill out your copyright notice in the Description page of Project Settings.


#include "FG3DMath/Public/ContextTarget.h"


AContextTarget::AContextTarget() {
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	TargetPositions.Add(FVector(-500.f, 0.f, 0.f));
	TargetPositions.Add(FVector(500.f, -500.f, 0.f));
	TargetPositions.Add(FVector(500.f, 500.f, 0.f));
	TargetPositions.Add(FVector(1000.f, 1000.f, 0.f));
	TargetPositions.Add(FVector(1000.f, -1000.f, 0.f));
	TargetPositions.Add(FVector(-1000.f, -1000.f, 0.f));
	TargetPositions.Add(FVector(-1000.f, 1000.f, 0.f));

	// Lerp to first positions over a few seconds
	Interpolation = new FInterpolation();
	AABBData = new FAABBData();
	WaitDuration = FMath::RandRange(1.f, 3.f);
	PositionIndex = FMath::RandRange(0, TargetPositions.Num() - 1);
}

void AContextTarget::SetMaterial(UMaterial* Material) const {
	if (MeshComponent->GetMaterial(0) != Material) {
		MeshComponent->SetMaterial(0, Material);
	}
}

void AContextTarget::UpdateAABBData() const {
	const auto ActorLocation = GetActorLocation();
	const auto ActorScale = GetActorScale();
	AABBData->MinX = ActorLocation.X;
	AABBData->MaxX = ActorLocation.X + 100.f * ActorScale.X;
	AABBData->MinY = ActorLocation.Y;
	AABBData->MaxY = ActorLocation.Y + 100.f * ActorScale.Y;
	AABBData->MinZ = ActorLocation.Z;
	AABBData->MaxZ = ActorLocation.Z + 100.f * ActorScale.Z;
}

void AContextTarget::Tick(float DeltaSeconds) {
	// Wait between Interpolations
	while (ShouldWait) {
		if (WaitTime < WaitDuration) {
			WaitTime += DeltaSeconds;
			return;
		}
		ShouldWait = false;
		WaitTime = 0.f;
		WaitDuration = FMath::RandRange(1.f, 3.f);
		Interpolation->Reset();
		Interpolation->Initialize(3.f);
		StartPosition = GetActorLocation();
	}

	// Interpolate
	TargetPosition = TargetPositions[PositionIndex];
	while (!Interpolation->Finished()) {
		Interpolate(DeltaSeconds);
		const float T = Interpolation->GetValue();
		const FVector InterpolationVector = FMath::Lerp(StartPosition, TargetPositions[PositionIndex], T);
		SetActorLocation(InterpolationVector);
		return;
	}

	// Set new target position
	ShouldWait = true;
	PositionIndex = FMath::RandRange(0, TargetPositions.Num() - 1);
}

bool AContextTarget::ShouldTickIfViewportsOnly() const {
	return true;
}

void AContextTarget::UpdateContext(const FVector& SourcePosition) const {
	const FVector ActorLocation = GetActorLocation();
	if (AABBData->bColliding) {
		SetMaterial(PurpleCollisionMat);
		return;
	}

	if (SourcePosition.X > ActorLocation.X) {
		SetMaterial(RedMat);
		return;
	}

	if (FVector::DotProduct((SourcePosition - ActorLocation).GetSafeNormal(), GetActorForwardVector()) < -0.7499f) {
		SetMaterial(GreenMat);
		return;
	}

	SetMaterial(YellowMat);
}

void AContextTarget::Interpolate(const float DeltaTime) const {
	Interpolation->Update(DeltaTime);
	Interpolation->EaseQuadInOut();
}
