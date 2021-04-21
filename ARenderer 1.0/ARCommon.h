#pragma once
#pragma once
namespace ARC {
	struct Point {
		double x = 0;
		double y = 0;
		double z = 0;
	};
	struct Triangle {
		Point A;
		Point B;
		Point C;
	};
	struct Voxel {
		Point Pos;
		bool isSet = false;
		signed short int BaseIlluminance = 0;
	};
	int coordinateToIndex(int x, int y, int w, int h);
	void clear_screen(char fill);

	double distance(Point A, Point B);

	Point rotateAlongX(Point P, Point O, double angle);
	Point rotateAlongZ(Point P, Point O, double angle);
	Point rotateAlongY(Point P, Point O, double angle);

};

//Model rotateAlongX(Model M, Point O, double angle) 