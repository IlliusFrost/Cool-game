#pragma once
#include <tga2d/sprite/sprite.h>
#include <..\CommonUtilities\InputHandler.hpp>
#include "CircleCollider.hpp"
#include "stdafx.h"
namespace Tga2D
{
	class CSprite;
}

class Player
{
public:
	Player(Vector2f aPosition, Sprite aSprite);
	Player();
	void Update(InputHandler* anInputHandler, float aTimeDelta);
	void Draw();
	int GetMass();
	Vector2f GetPosition();
private:
	Vector2f myPosition = { 0, 0 };
	Vector2f myVelocity = { 0,0 };
	Sprite mySprite;
	int myMass;
	bool isGrounded;
	CircleCollider* myCollider;
};