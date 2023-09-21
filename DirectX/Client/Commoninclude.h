#pragma once

// WinAPI
#include "framework.h"
#include "Client.h"

// unique_point
#include<memory>

// ComPtr
#include<wrl.h>

// DX11
#include <d3d11_1.h>
#pragma comment(lib,"d3d11.lib")
#include<d3dcompiler.h>
#pragma comment(lib, "d3dcompiler.lib")

#include<DirectXTex.h>

#include <string>
#include <assert.h>

// Data Structure
#include <vector>
#include <map>
#include <bitset>

#include "EHMath.h"

// eunm class
namespace EH::enums
{
	enum class eCommponentType
	{
		Transform
		, MeshRenderer
		, Script
		, End
	};


	enum class eLayerType
	{
		BackGround
		, UI
		, Bullet
		, Enemy
		, Player
		, End
	};

	enum class CBYTES
	{
		  Transform
		, None
		, END
	};
}

namespace EH::graphics
{
	enum class ShaderStage
	{
		VS,		// Vertex Shader
		HS,		// Hull Shader
		DS,		// Domain Shader
		GS,		// Geometry Shader
		PS,		// Pixel Shader
		CS,		// Compute Shader
		NONE,
	};
}
