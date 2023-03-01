#include "projMat.h"

projMat::projMat()
{
	projectionMatrix.m[0][0] = AspectRatio * FovRad;
	projectionMatrix.m[1][1] = FovRad;
	projectionMatrix.m[2][2] = Far / (Far - Near);
	projectionMatrix.m[3][2] = (-Far * Near) / (Far - Near);
	projectionMatrix.m[2][3] = 1.0f;
	projectionMatrix.m[3][3] = 0.0f;
}

void projMat::setAspectRatio(int screenHeight, int screenWidth)
{
	AspectRatio = (float)screenHeight / (float)screenWidth;
}
