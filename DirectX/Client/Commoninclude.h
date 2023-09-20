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

#include <string>
#include <assert.h>

// Data Structure
#include <vector>

#include "EHMath.h"

// eunm class
namespace EH::enums
{
	enum class eCommponentType
	{
		Transform
		, End
	};
}
