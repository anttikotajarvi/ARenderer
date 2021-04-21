#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <cwchar>
#include <math.h>

#include "Palette.h"
#include "ARCommon.h"
#include "VMap.h"
#include "Models.h"
#include "ConsoleManager.h"

class ARenderer {
	std::string canvas;
	Palette palette;
public:
	int sw;
	int sh;
	int vertical_FOV = 70;
	int horizontal_FOV = 70;
	int focal_length;
	char blank_char = ' ';
	VMap MainVMap;
	ConsoleManager CM;

	ARenderer(Palette p, int w, int h);
	Palette getPalette();

	std::vector<Point> getLine(Point A, Point B);
	bool drawLine(Point A, Point B, char X);
	bool setPixel(int x, int y, char a, int attr = 15);
	int vyToLy(double y, double z);
	int vxToLx(double x, double z);
	Point projectVirtualPoint(Point a);

	VMap build(Triangle P);
	void buildModel(Models::Model M, Point O, double scale, double angle);
	void placeVMap(VMap Map);
	void render(VMap Map);
	void render();
};