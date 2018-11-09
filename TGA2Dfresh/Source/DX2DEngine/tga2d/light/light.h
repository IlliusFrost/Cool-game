#pragma once
#include "tga2d/engine_defines.h"

namespace Tga2D
{
	class CLight
	{
	public:
#ifdef USE_LIGHTS
		CLight();
#else
#pragma message("CLight:: You have undifined the usage of lights, and yet you use the Light class, this will not have the behavior you intended")
		 CLight();
#endif // USE_LIGHTS

		
		~CLight();
		void Render();
		Vector2f myPosition;
		Vector4f myColor;
		float myIntensity;
		float myFallOff;
	};
}