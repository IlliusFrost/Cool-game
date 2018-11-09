// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"
#include <tga2d/drawers/debug_drawer.h>
#include <tga2d/error/error_manager.h>
#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

#include "../CommonUtilities/Macro.hpp"
#include "../CommonUtilities/Math/Vector.hpp"
#include "../CommonUtilities/Containers/GrowingArray.hpp"
#include <tga2d/sprite/sprite.h>

typedef CommonUtilities::Vector2<float> Vector2f;
typedef CommonUtilities::Vector3<float> Vector3f;
typedef Tga2D::CSprite* Sprite;

using namespace CommonUtilities;

// TODO: reference additional headers your program requires here
