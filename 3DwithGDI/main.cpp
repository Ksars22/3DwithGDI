#include <Windows.h>
#include <vector>
#include <algorithm>
#include "structs.h"
#include "projMat.h"
#include "objects.h"
#include "engine.h"

vec3 camera;
cube firstCube;
projMat projectionMat;
bool running;
const auto IDT_TIMER_1 = 1;
float theta = .1f;
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

	WNDCLASS wc = {};
	const wchar_t class_name[] = L"3DwithGDI";
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = class_name;


	RegisterClass(&wc);

	HWND hwnd = CreateWindowEx(
		0,
		class_name,
		L"3DwithGDI",
		WS_OVERLAPPEDWINDOW,

		//size and pos
		CW_USEDEFAULT, CW_USEDEFAULT, 1920, 1080,

		NULL,
		NULL,
		hInstance,
		NULL
	);

	if (hwnd == NULL)
	{
		return 0;
	}
	firstCube.mCube.LoadFromObjectFile("C:/Users/13179/Desktop/videoShip.obj");

	SetTimer(hwnd, IDT_TIMER_1, 30, NULL);
	ShowWindow(hwnd, nCmdShow);
	MSG msg = { };
	running = true;
	while (running)
	{
		while (GetMessage(&msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	RECT client;
	GetClientRect(hwnd, &client);

	switch (uMsg)
	{
	case WM_TIMER:
		switch (wParam)
		{
		case IDT_TIMER_1:

			HDC hdc = GetDC(hwnd);
			SelectObject(hdc, GetStockObject(2));

			FillRect(hdc, &client, (HBRUSH)(COLOR_WINDOW + 1)); //fill the screen black
			mat4x4 rotZ, rotX;
			theta += .1;

			// rotation matrix Z
			rotZ.m[0][0] = cosf(theta);
			rotZ.m[0][1] = sinf(theta);
			rotZ.m[1][0] = -sinf(theta);
			rotZ.m[1][1] = cosf(theta);
			rotZ.m[2][2] = 1;
			rotZ.m[3][3] = 1;

			// rotation matrix X

			rotX.m[0][0] = 1;
			rotX.m[1][1] = cosf(theta * 0.5f);
			rotX.m[1][2] = sinf(theta * 0.5f);
			rotX.m[2][1] = -sinf(theta * 0.5f);
			rotX.m[2][2] = cosf(theta * 0.5f);
			rotX.m[3][3] = 1;
			
			std::vector<triangle> toRaster;

			for (auto tri : firstCube.mCube.tris) // for each triangle in cube mesh
			{
				triangle triProjected, triTranslated, triRotatedZ, triRotatedZX;

				MultiplyMatrixVector(tri.p[0], triRotatedZ.p[0], rotZ);
				MultiplyMatrixVector(tri.p[1], triRotatedZ.p[1], rotZ);
				MultiplyMatrixVector(tri.p[2], triRotatedZ.p[2], rotZ);

				MultiplyMatrixVector(triRotatedZ.p[0], triRotatedZX.p[0], rotX);
				MultiplyMatrixVector(triRotatedZ.p[1], triRotatedZX.p[1], rotX);
				MultiplyMatrixVector(triRotatedZ.p[2], triRotatedZX.p[2], rotX);

				triTranslated = triRotatedZX;
				triTranslated.p[0].z = triRotatedZX.p[0].z + 10.0f;
				triTranslated.p[1].z = triRotatedZX.p[1].z + 10.0f;
				triTranslated.p[2].z = triRotatedZX.p[2].z + 10.0f;

				vec3 normal, line1, line2;
				line1.x = triTranslated.p[1].x - triTranslated.p[0].x;
				line1.y = triTranslated.p[1].y - triTranslated.p[0].y;
				line1.z = triTranslated.p[1].z - triTranslated.p[0].z;

				line2.x = triTranslated.p[2].x - triTranslated.p[0].x;
				line2.y = triTranslated.p[2].y - triTranslated.p[0].y;
				line2.z = triTranslated.p[2].z - triTranslated.p[0].z;

				normal.x = line1.y * line2.z - line1.z * line2.y;
				normal.y = line1.z * line2.x - line1.x * line2.z;
				normal.z = line1.x * line2.y - line1.y * line2.x;

				float l = sqrtf(normal.x*normal.x + normal.y*normal.y + normal.z*normal.z);
				normal.x /= l; normal.y /= l; normal.z /= l;

				if (normal.x * (triTranslated.p[0].x - camera.x) + normal.y * (triTranslated.p[0].y - camera.y) + normal.z * (triTranslated.p[0].z - camera.z) < 0.0f)
				{
					// Project 3D -> 2D
					MultiplyMatrixVector(triTranslated.p[0], triProjected.p[0], projectionMat.projectionMatrix);
					MultiplyMatrixVector(triTranslated.p[1], triProjected.p[1], projectionMat.projectionMatrix);
					MultiplyMatrixVector(triTranslated.p[2], triProjected.p[2], projectionMat.projectionMatrix);

					triProjected.p[0].x += 1.0f; triProjected.p[0].y += 1.0f;
					triProjected.p[1].x += 1.0f; triProjected.p[1].y += 1.0f;
					triProjected.p[2].x += 1.0f; triProjected.p[2].y += 1.0f;

					triProjected.p[0].x *= 0.5f * (float)(client.right - client.left);
					triProjected.p[0].y *= 0.5f * (float)(client.bottom - client.top);
					triProjected.p[1].x *= 0.5f * (float)(client.right - client.left);
					triProjected.p[1].y *= 0.5f * (float)(client.bottom - client.top);
					triProjected.p[2].x *= 0.5f * (float)(client.right - client.left);
					triProjected.p[2].y *= 0.5f * (float)(client.bottom - client.top);

					toRaster.push_back(triProjected);

				}
			}
			
			//sort triangles back to front
			sort(toRaster.begin(), toRaster.end(), [](triangle& t1, triangle& t2)
				{
					float z1 = (t1.p[0].z + t1.p[1].z + t1.p[2].z) / 3.0f;
					float z2 = (t2.p[0].z + t2.p[1].z + t2.p[2].z) / 3.0f;
					return z1 > z2;
				});

			for (auto& triProjected : toRaster)
			{
				fillTriangle(hdc, triProjected.p[0].x, triProjected.p[0].y, triProjected.p[1].x, triProjected.p[1].y, triProjected.p[2].x, triProjected.p[2].y);
			}

			ReleaseDC(hwnd, hdc);
			return 0;
		}
		break;
	case WM_DESTROY:
	{
		running = false;
		PostQuitMessage(0);
		return 0;
	}
	return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}
