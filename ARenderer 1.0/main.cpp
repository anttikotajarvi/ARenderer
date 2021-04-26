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

	Triangle Example{
		{10,10,10},
		{20,150,60},
		{150,100,180}
	};		
	d.placeVMap(d.build(Example));
	d.render();
	d.CM.print();

	return 0;

}
