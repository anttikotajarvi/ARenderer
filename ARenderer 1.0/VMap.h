#pragma once

#include <vector>
#include "ARCommon.h"

using namespace ARC;

class VMap {
	std::vector<Voxel> data;
public:
	const int width;
	const int height;
	const int length;
	Point O;

	VMap(int w, int h, int x, int y);
	bool setData(int x, int y, Voxel V);
	bool setData(int i, Voxel V);
	Voxel getData(int i);
	Voxel getData(int x, int y);
	void resetData();
};
