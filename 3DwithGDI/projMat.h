#pragma once
#include <math.h>
#include "structs.h"

#define M_PI

class projMat {
public:
	projMat();
	mat4x4 projectionMatrix;
	float Near = 0.1f;
	float Far = 1000.0f;
	float Fov = 90.0f;
	float AspectRatio = float(1080) / float(1920);
	float FovRad = 1.0f / tanf(Fov * 0.5f / 180.0f * 3.14159f);



	void setAspectRatio(int screenHeight, int screenWidth);
};