#include "structs.h"
#include <fstream>
#include <strstream>
#include <vector>

void MultiplyMatrixVector(vec3& inputVector, vec3& outputVector, mat4x4& matrix)
{
	outputVector.x = inputVector.x * matrix.m[0][0] + inputVector.y * matrix.m[1][0] + inputVector.z * matrix.m[2][0] + matrix.m[3][0];
	outputVector.y = inputVector.x * matrix.m[0][1] + inputVector.y * matrix.m[1][1] + inputVector.z * matrix.m[2][1] + matrix.m[3][1];
	outputVector.z = inputVector.x * matrix.m[0][2] + inputVector.y * matrix.m[1][2] + inputVector.z * matrix.m[2][2] + matrix.m[3][2];
	float w = inputVector.x * matrix.m[0][3] + inputVector.y * matrix.m[1][3] + inputVector.z * matrix.m[2][3] + matrix.m[3][3];

	if (w != 0.0f)
	{
		outputVector.x /= w; outputVector.y /= w; outputVector.z /= w;
	}
}

bool Mesh::LoadFromObjectFile(std::string fileName)
{
	std::ifstream f(fileName);
	if (!f.is_open())
	{
		return false;
	}
	//cache of verts
	std::vector<vec3> verts;

	while (!f.eof())
	{
		char line[128];
		f.getline(line, 128);

		std::strstream s;
		s << line;

		char junk;

		if (line[0] == 'v')
		{
			vec3 v;
			s >> junk >> v.x >> v.y >> v.z;
			verts.push_back(v);
		}

		if (line[0] == 'f')
		{
			int f[3];
			s >> junk >> f[0] >> f[1] >> f[2];
			tris.push_back({ verts[f[0] - 1], verts[f[1] - 1], verts[f[2] - 1] });
		}
	}
	return true;
}
