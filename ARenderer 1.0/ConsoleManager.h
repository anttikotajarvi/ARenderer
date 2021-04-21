#pragma once

#include <windows.h>
class ConsoleManager {
public:
	const int w;
	const int h;
	HANDLE wHnd;
	HANDLE rHnd;
	SMALL_RECT windowSize;
	COORD bufferSize;
	COORD characterBufferSize;
	COORD characterPosition;
	SMALL_RECT consoleWriteArea;
	CHAR_INFO* consoleBuffer;
	ConsoleManager(int w, int h);
	void resetConsoleBuffer();
	void print();
};