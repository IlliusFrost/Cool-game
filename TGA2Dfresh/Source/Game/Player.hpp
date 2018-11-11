#pragma once
#include <tga2d/sprite/sprite.h>
#include <..\CommonUtilities\InputHandler.hpp>
#include "CircleCollider.hpp"
#include "stdafx.h"
#include "GameObjectData.h"
namespace Tga2D
{
	class CSprite;
}
class UIManager;
class Player
{
public:
	Player(Vector2f aPosition, Sprite aSprite);
	Player();
	void Update(InputHandler* anInputHandler, float aTimeDelta, UIManager* aUIManager);
	void Draw();
	int GetMass();
	void ModifyMass(int anAmountToModify);
	Vector2f GetPosition();
private:
	CircleCollider* myCircleCollider;
	ObjectData myData;
};