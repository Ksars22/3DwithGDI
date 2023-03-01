#pragma once
#include <Windows.h>
#include "structs.h"

void drawTriangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3);
void fillTriangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3);

int GetColor(float lum);