#include <Windows.h>

#include "ConsoleManager.h"

ConsoleManager::ConsoleManager(int w, int h) : w(w), h(h) {
	windowSize = { 0, 0, (SHORT)w - 1, (SHORT)h - 1 };
	bufferSize = { (SHORT)w, (SHORT)h };
	characterBufferSize = { (SHORT)w, (SHORT)h };
	characterPosition = { 0, 0 };
	consoleWriteArea = { 0, 0, (SHORT)w - 1, (SHORT)h - 1 };

	wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	rHnd = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, bufferSize);

	consoleBuffer = new CHAR_INFO[w * h];
}
void ConsoleManager::resetConsoleBuffer() {
	delete[] consoleBuffer;
	consoleBuffer = new CHAR_INFO[w * h];
};
void ConsoleManager::print() {
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPosition, &consoleWriteArea);
}