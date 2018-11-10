#pragma once
#include <tga2d/sprite/sprite.h>
#include "CircleCollider.hpp"
#include "GameObjectData.h"
namespace Tga2D
{
	class CSprite;
}
class Player;
class PickUp
{
public:
	void Draw();
	PickUp(Vector2f aPosition, Sprite aSprite);
	~PickUp();
	bool GetIfIsRemoved();
private:
	CircleCollider* myCircleCollider;
	Sprite mySprite;
	bool isRemoved = false; 
	ObjectData myData;
};