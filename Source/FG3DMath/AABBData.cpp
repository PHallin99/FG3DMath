#include "AABBData.h"

bool FAABBData::IsColliding(const FAABBData* Other) const {
	if (MaxX < Other->MinX || MinX > Other->MaxX) return false;
	if (MaxY < Other->MinY || MinY > Other->MaxY) return false;
	if (MaxZ < Other->MinZ || MinZ > Other->MaxZ) return false;
	return true;
}
