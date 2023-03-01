#pragma once
#include <vector>
#include <string>
#include <Windows.h>


struct vec3 {
	float x, y, z;
};

struct triangle {
	vec3 p[3];

	int col;
};

struct Mesh {
	std::vector<triangle> tris;

	bool LoadFromObjectFile(std::string fileName);
};

struct mat4x4 {
	float m[4][4] = { 0 };
};

void MultiplyMatrixVector(vec3& inputVector, vec3& outputVector, mat4x4& matrix);
