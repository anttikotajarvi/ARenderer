#include <windows.h>
#include <iostream>
#include <vector>

#include "Palette.h"

Palette classic{
	{'.',',','-','~',':',';','=','!','*','#','$','@'},
	{15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 ,15 }
};
Palette smooth{
	{176, 176, 176, 178, 176, 177, 178, 177, 178, 176, 178, 176, 176, 177, 177, 177, 178, 178, 176, 177, 176, 176, 176, 176, 176, 176},
	{0	, 8	 ,   7, 128,  15,   7, 240,  15,   8, 128, 136, 135, 143, 135, 143, 112,   7,  15, 112, 240, 120, 119, 127, 240, 248, 247, }
};
