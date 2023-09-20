#pragma once

#include "Commoninclude.h"
#include "EHMesh.h"
#include "EHShader.h"

namespace EH::renderer
{
	struct Vertex
	{
		Math::Vector3 pos;
		Math::Vector4 Color;
	};

	void Initialize();
	void Release();

	extern Mesh* mesh;
	extern Shader* shader;
}

