#include <iostream>
#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <cwchar>
#include <math.h>
#include <chrono>


#include "ARCommon.h"
#include "VMap.h"
#include "ARenderer.h"
#include "Palette.h"
#include "Models.h"
#include "ConsoleManager.h"

#define SCREEN_WIDTH 200
#define SCREEN_HEIGHT 200

#define M_PI 3.14159265358979323846

int main() {

	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = 4;
	cfi.dwFontSize.Y = 4;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &cfi);


	ARenderer d(classic, SCREEN_WIDTH, SCREEN_HEIGHT);

	ARC::Models::Model teapot = ARC::Models::import_obj("C:\\Users\\40oz\\Downloads\\teapot.obj");
	Point O{ 80, 50, 100 };

	d.buildModel(teapot, O, 30, 0.05);

	d.render();
	d.CM.print();
	return 0;

}

//int tBuild, tPlace, tRender, tPrint, tRotate;
//200iterations rendering Average 66ms
