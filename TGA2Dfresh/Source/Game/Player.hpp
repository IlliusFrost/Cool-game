#pragma once
#include <tga2d/sprite/sprite.h>
#include <..\CommonUtilities\InputHandler.hpp>
#include "stdafx.h"
namespace Tga2D
{
	class CSprite;
}

class Player
{
public:
	Player(Vector2f aPosition, Tga2D::CSprite* aSprite);
	Player();
	void Update(InputHandler* anInputHandler);
	void Draw();
private:
	Vector2f myPosition = { 0, 0 };
	Tga2D::CSprite* mySprite;
};