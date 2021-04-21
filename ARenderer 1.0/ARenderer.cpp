#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <cwchar>
#include <math.h>

#include "ARenderer.h"
#include "ConsoleManager.h"
#include "VMap.h"
#include "ARCommon.h"

using namespace ARC;



ARenderer::ARenderer(Palette p, int w, int h) : MainVMap(w, h, 0, 0), CM(ConsoleManager(w, h)), palette(p), focal_length(w) {
	sw = w;
	sh = h;
	canvas = std::string(sw * sh, ' ');

}

Palette ARenderer::getPalette() { return palette; }

std::vector<Point> ARenderer::getLine(Point A, Point B) {
	double slope = (double)(B.y - A.y) / (B.x - A.x);
	int ai = 0;

	std::vector<Point> arr;

	if (abs(slope) <= 1.00) {
		if (A.x <= B.x) {
			for (double i = A.x; i <= B.x; i++) {
				arr.push_back(Point{ i, (double)(int)(0.5 + (i - A.x) * slope + A.y) });
			}
			return arr;
		}
		else {
			for (double i = B.x; i <= A.x; i++) {
				arr.push_back(Point{ i, (double)(int)(0.5 + (i - B.x) * slope + B.y) });
			}
			return arr;
		}
	}
	else {
		if (A.y <= B.y) {
			for (double i = A.y; i <= B.y; i++) {
				arr.push_back(Point{ (double)(int)(0.5 + (i - A.y) / slope + A.x), i });
			}
			return arr;
		}
		else {
			for (double i = B.y; i <= A.y; i++) {
				arr.push_back(Point{ (double)(int)(0.5 + (i - B.y) / slope + B.x), i });
			}
			return arr;
		}
	}
}
bool ARenderer::drawLine(Point A, Point B, char X) {
	std::vector<Point> arr = getLine(A, B);
	int ll = arr.size();
	for (int i = 0; i < ll; i++) {
		setPixel((int)arr[i].x, (int)arr[i].y, X);
	}
	return true;
}
bool ARenderer::setPixel(int x, int y, char a, int attr) {
	if (x < 0 || y < 0 || x >= sw || y >= sh) return false;
	int i = coordinateToIndex(x, y, sw, sh);
	CM.consoleBuffer[i].Char.UnicodeChar = (WCHAR)a;
	CM.consoleBuffer[i].Attributes = attr;

	return true;
}
int ARenderer::vyToLy(double y, double z) {
	return (int)0.5 + sw / (sh + 2 * ((double)vertical_FOV / 90 * z)) * (y + ((double)vertical_FOV / 90 * z));
}
int ARenderer::vxToLx(double x, double z) {
	return (int)0.5 + sw / (sh + 2 * ((double)horizontal_FOV / 90 * z)) * (x + ((double)horizontal_FOV / 90 * z));
}
Point ARenderer::projectVirtualPoint(Point a) {
	return Point{ (double)vxToLx(a.x, a.z), (double)vyToLy(a.y, a.z) };
}
VMap ARenderer::build(Triangle P) {
	Triangle PP{ projectVirtualPoint(P.A), projectVirtualPoint(P.B), projectVirtualPoint(P.C) }; // Projected Polygon (PP)

	Point min{ PP.A.x, PP.A.y };
	Point max{ PP.A.x, PP.A.y };
	if (min.x > PP.B.x) min.x = PP.B.x;
	if (min.x > PP.C.x) min.x = PP.C.x;
	if (min.y > PP.B.y) min.y = PP.B.y;
	if (min.y > PP.C.y) min.y = PP.C.y;
	if (max.x < PP.B.x) max.x = PP.B.x;
	if (max.x < PP.C.x) max.x = PP.C.x;
	if (max.y < PP.B.y) max.y = PP.B.y;
	if (max.y < PP.C.y) max.y = PP.C.y;

	VMap TempVMap(max.x - min.x + 1, max.y - min.y, min.x, min.y);

	std::vector<Point> lineAB = getLine(PP.A, PP.B);
	std::vector<Point> lineAC = getLine(PP.A, PP.C);
	std::vector<Point> lineBC = getLine(PP.B, PP.C);

	double ABd = distance(PP.A, PP.B);
	int lineABsize = lineAB.size();
	for (int pi = 0; pi < lineABsize; pi++) {
		double this_d = distance(PP.A, lineAB[pi]);
		TempVMap.setData((int)lineAB[pi].x - min.x, (int)lineAB[pi].y - min.y, Voxel{
			Point{
				P.A.x + this_d / ABd * (P.B.x - P.A.x),
				P.A.y + this_d / ABd * (P.B.y - P.A.y),
				P.A.z + this_d / ABd * (P.B.z - P.A.z)
			},
			true,
			8
			});
	}
	double ACd = distance(PP.A, PP.C);
	int lineACsize = lineAC.size();
	for (int pi = 0; pi < lineACsize; pi++) {
		double this_d = distance(PP.A, lineAC[pi]);
		TempVMap.setData((int)lineAC[pi].x - min.x, (int)lineAC[pi].y - min.y, Voxel{
			Point{
				P.A.x + this_d / ACd * (P.C.x - P.A.x),
				P.A.y + this_d / ACd * (P.C.y - P.A.y),
				P.A.z + this_d / ACd * (P.C.z - P.A.z)
			},
			true,
			8
			});
	}
	double BCd = distance(PP.B, PP.C);
	int lineBCsize = lineBC.size();
	for (int pi = 0; pi < lineBCsize; pi++) {
		double this_d = distance(PP.B, lineBC[pi]);
		TempVMap.setData((int)lineBC[pi].x - min.x, (int)lineBC[pi].y - min.y, Voxel{
			Point{
				P.B.x + this_d / BCd * (P.C.x - P.B.x),
				P.B.y + this_d / BCd * (P.C.y - P.B.y),
				P.B.z + this_d / BCd * (P.C.z - P.B.z)
			},
			true,
			8
			});
	}

	// Scanline rasterization
	Point StartPP;
	Point EndPP;
	int search_state;							// 0: none found, 1: start found, 2: start and end found
	int current_index;
	for (int y = 0; y < TempVMap.height; y++) {
		search_state = 0;
		for (int x = 0; x < TempVMap.width; x++) {
			current_index = coordinateToIndex(x, y, TempVMap.width, TempVMap.height);
			if (TempVMap.getData(current_index).isSet == true) {
				if (search_state == 0) {
					StartPP = Point{ (double)x, (double)y };
					search_state = 1;
				}
				else if (search_state == 1 && TempVMap.getData(current_index - 1).isSet == false) {
					EndPP = Point{ (double)x, (double)y };
					search_state = 2;
				}
			}
		}
		if (search_state == 2) {
			Point StartVP = TempVMap.getData(StartPP.x, StartPP.y).Pos;
			Point EndVP = TempVMap.getData(EndPP.x, EndPP.y).Pos;

			double line_d = EndPP.x - StartPP.x;
			for (int x = StartPP.x + 1; x < EndPP.x; x++) {
				int vmap_index = coordinateToIndex(x, StartPP.y, TempVMap.width, TempVMap.height);

				double this_d = x - StartPP.x;

				TempVMap.setData(vmap_index, Voxel{
					Point{
						StartVP.x + this_d / line_d * (EndVP.x - StartVP.x),
						StartVP.y + this_d / line_d * (EndVP.y - StartVP.y),
						StartVP.z + this_d / line_d * (EndVP.z - StartVP.z)
					},
					true
					});
			}
		}
	}

	return TempVMap;
}
void ARenderer::buildModel(Models::Model M, Point O, double scale, double angle) {
	int model_size = M.f.size();
	for (int i = 0; i < model_size; i++) {
		Point A = M.v[M.f[i][0]];
		Point B = M.v[M.f[i][1]];
		Point C = M.v[M.f[i][2]];
		placeVMap(build({
			rotateAlongY({O.x + scale * A.x, O.y + scale * A.y, O.z + scale * A.z}, O, angle),
			rotateAlongY({O.x + scale * B.x, O.y + scale * B.y, O.z + scale * B.z}, O, angle),
			rotateAlongY({O.x + scale * C.x, O.y + scale * C.y, O.z + scale * C.z}, O, angle)
			}));
	}
}
void ARenderer::placeVMap(VMap Map) {
	for (int y = 0; y < Map.height; y++) {
		for (int x = 0; x < Map.width; x++) {
			Voxel SourceVoxel = Map.getData(x, y);
			if (SourceVoxel.isSet == true) {
				Voxel TargetVoxel = MainVMap.getData(x + Map.O.x, y + Map.O.y);
				if (TargetVoxel.isSet == false || TargetVoxel.Pos.z > SourceVoxel.Pos.z) MainVMap.setData(x + Map.O.x, y + Map.O.y, SourceVoxel);
			}
		}
	}
}

void ARenderer::render(VMap Map) {
	for (int y = 0; y < Map.height; y++) for (int x = 0; x < Map.width; x++) {
		Voxel Current = Map.getData(x, y);
		if (Current.isSet == true) {
			int palette_length = palette.c.size();
			int palette_index = (int)(0.5 + (double)palette_length - (double)Current.Pos.z / focal_length * (double)palette_length) - 1; //handles brightness
			if (palette_index < 0) palette_index = 0;
			if (palette_index >= palette_length) palette_index = palette_length - 1;
			setPixel(
				x + Map.O.x,
				y + Map.O.y,
				palette.c[palette_index],
				palette.a[palette_index]
			);
		}
		else {
			setPixel(x + Map.O.x, y + Map.O.y, blank_char, 15);
		}
	}
}
void ARenderer::render() {
	render(MainVMap);
}
