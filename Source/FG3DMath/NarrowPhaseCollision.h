#pragma once

class FAABBData;

class FNarrowPhaseCollision {
public:
	static void Update(TArray<FAABBData*> AABBs);

private:
	TArray<FAABBData*> ObjectsWithAABB;
};
