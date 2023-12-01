#include "FG3DMath/Public/ContextSource.h"


AContextSource::AContextSource() {
	PrimaryActorTick.bCanEverTick = true;
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	Collision = new FNarrowPhaseCollision();
}

bool AContextSource::ShouldTickIfViewportsOnly() const {
	return true;
}

void AContextSource::Tick(float DeltaTime) {
	TArray<FAABBData*> AABBs;
	for (const auto Target : ContextTargets) {
		Target->UpdateAABBData();
		Target->UpdateContext(GetActorLocation());
		AABBs.Add(Target->AABBData);
	}

	Collision->Update(AABBs);
}
