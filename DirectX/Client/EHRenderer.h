#pragma once

#include "Commoninclude.h"
#include "EHMesh.h"
#include "EHShader.h"
#include "EHConstantBuffer.h"

namespace EH::renderer
{
	struct Vertex
	{
		Math::Vector3 pos;
		Math::Vector4 Color;
	};

	struct CBUFFER
	{
		Math::Vector3 pos;
		int pad1;
		Math::Vector3 scale;
		int pad2;
	};

	void Initialize();
	void Release();

	extern Mesh* mesh;
	extern Mesh* mesh1;
	extern Shader* shader;
	extern ConstantBuffer* constantBuffers[];
}

