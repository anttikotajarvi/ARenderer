#pragma once

#include <vector>
#include "VMap.h"
#include "ARCommon.h"

using namespace ARC;

VMap::VMap(int w, int h, int x, int y) : width(w), height(h), length(w* h), O(Point{ (double)x,(double)y }) {
	data.resize(w * h);
}
bool VMap::setData(int x, int y, Voxel V) {
	if (x < 0 || y < 0 || x >= width || y >= height) return false;
	data[coordinateToIndex(x, y, width, height)] = V;
	return true;
}
bool VMap::setData(int i, Voxel V) {
	if (i < 0 || i >= length) return false;
	data[i] = V;
	return true;
}
Voxel VMap::getData(int i) {
	if (i < 0 || i >= length) return Voxel{ Point{0,0,0}, false };
	return data[i];
}
Voxel VMap::getData(int x, int y) {
	if (x < 0 || y < 0 || x >= width || y >= height) return Voxel{ Point{0,0,0}, false };
	return data[coordinateToIndex(x, y, width, height)];
}
void VMap::resetData() {
	data.clear();
	data.resize(width * height);
}

