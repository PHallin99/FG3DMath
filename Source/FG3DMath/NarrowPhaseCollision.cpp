#include "NarrowPhaseCollision.h"

#include "AABBData.h"

void FNarrowPhaseCollision::Update(TArray<FAABBData*> AABBs) {
	for (const auto i : AABBs) {
		bool bCollision = false;
		for (const auto j : AABBs) {
			if (i == j || bCollision) {
				continue;
			}

			bCollision = i->IsColliding(j);
		}

		if (!i->bColliding && bCollision) {
			i->bColliding = bCollision;
		}

		if (i->bColliding && !bCollision) {
			i->bColliding = bCollision;
		}
	}
}
