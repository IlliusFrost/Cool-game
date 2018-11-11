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
	void Update(float aDeltaTime);
	PickUp(Vector2f aPosition, Sprite aSprite,Vector2f aDirection);
	~PickUp();
	CircleCollider* GetCollider();
	ObjectData GetData();
private:
	CircleCollider* myCircleCollider;
	Sprite mySprite;
	ObjectData myData;
};