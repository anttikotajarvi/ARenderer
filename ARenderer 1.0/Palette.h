#pragma once
#include <iostream>
#include <vector>
#include <windows.h>

struct Palette {
	std::vector<WCHAR> c;
	std::vector<int> a;
};

extern struct Palette classic, smooth;