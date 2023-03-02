#include "engine.h"
#include <windows.h>
#include <stdlib.h>

void drawTriangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x3, y3);
	LineTo(hdc, x1, y1);

}

void fillTriangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3)
{

	//SelectObject(hdc, GetStockObject(col));

	POINT verts[3];
	verts[0].x = x1;
	verts[0].y = y1;
	verts[1].x = x2;
	verts[1].y = y2;
	verts[2].x = x3;
	verts[2].y = y3;

	Polygon(hdc, verts, 3);
}

int GetColor(float lum)
{
	int color;
	int pixel_bw = (int)(13.0f * lum);
	switch (pixel_bw)
	{
	case 0:
		color = 7;
		break;
	case 1:
		color = 7;
		break;
	case 2:
		color = 2;
		break;
	case 3:
		color = 2;
		break;
	case 4:
		color = 3;
		break;
	case 5:
		color = 3;
		break;
	case 6:
		color = 4;
		break;
	case 7:
		color = 4;
		break;
	case 8:
		color = 4;
		break;
	case 9:
		color = 5;
		break;
	case 10:
		color = 5;
		break;
	case 11:
		color = 6;
		break;
	case 12:
		color = 6;
		break;
	default:
		color = 4;
		break;
	}

	return color;
}
