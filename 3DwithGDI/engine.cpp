#include "engine.h"

void drawTriangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
	LineTo(hdc, x3, y3);
	LineTo(hdc, x1, y1);

}

void fillTriangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3)
{
	POINT verts[3];
	verts[0].x = x1;
	verts[0].y = y1;
	verts[1].x = x2;
	verts[1].y = y2;
	verts[2].x = x3;
	verts[2].y = y3;

	Polygon(hdc, verts, 3);
}
