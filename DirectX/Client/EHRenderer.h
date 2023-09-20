#pragma once

#include "Commoninclude.h"

namespace EH
{
	class Renderer
	{
		struct Vertex
		{
			Math::Vector3 pos;
			Math::Vector4 Color;
		};

		void Initialize();
		void Release();
	};
}

