#pragma once

class FAABBData {
public:
	float MaxX = 0;
	float MinX = 0;
	float MaxY = 0;
	float MinY = 0;
	float MaxZ = 0;
	float MinZ = 0;
	bool bColliding;

	bool IsColliding(const FAABBData* Other) const;
};
