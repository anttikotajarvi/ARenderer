#pragma once
#include <windows.h>
#include <math.h>
#include "ARCommon.h"

using namespace ARC;

int ARC::coordinateToIndex(int x, int y, int w, int h) {
	return (h - y - (y >= h ? 0 : 1)) * w + x;
}
double ARC::distance(Point A, Point B) {
	return pow(pow((B.x - A.x), 2.0) + pow((B.y - A.y), 2.0) + pow((B.z - A.z), 2.0), 0.5);
}
void ARC::clear_screen(char fill = ' ') {
	COORD tl = { 0,0 };
	CONSOLE_SCREEN_BUFFER_INFO s;
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(console, &s);
	DWORD written, cells = s.dwSize.X * s.dwSize.Y;
	FillConsoleOutputCharacter(console, fill, cells, tl, &written);
	FillConsoleOutputAttribute(console, s.wAttributes, cells, tl, &written);
	SetConsoleCursorPosition(console, tl);
};
Point ARC::rotateAlongX(Point P, Point O, double angle) {
	double s = sin(angle);
	double c = cos(angle);

	P.y -= O.y;
	P.z -= O.z;

	double xnew = P.y * c - P.z * s;
	double ynew = P.y * s + P.z * c;

	P.y = xnew + O.y;
	P.z = ynew + O.x;
	return P;

}
Point ARC::rotateAlongZ(Point P, Point O, double angle) {
	double s = sin(angle);
	double c = cos(angle);

	P.x -= O.x;
	P.y -= O.y;

	double xnew = P.x * c - P.y * s;
	double ynew = P.x * s + P.y * c;

	P.x = xnew + O.x;
	P.y = ynew + O.y;
	return P;

}
Point ARC::rotateAlongY(Point P, Point O, double angle) {
	double s = sin(angle);
	double c = cos(angle);

	P.x -= O.x;
	P.z -= O.z;

	double xnew = P.x * c - P.z * s;
	double ynew = P.x * s + P.z * c;

	P.x = xnew + O.x;
	P.z = ynew + O.z;
	return P;

}
