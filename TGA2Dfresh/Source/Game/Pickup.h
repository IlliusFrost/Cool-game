#pragma once
#include <tga2d/sprite/sprite.h>
#include "CircleCollider.hpp"
#include "GameObjectData.h"
#include <tga2d/shaders/customshader.h>
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
	PickUp(Vector2f aPosition, Sprite aSprite,Vector2f aDirection, Tga2D::CCustomShader* aCustomShader);
	~PickUp();
	CircleCollider* GetCollider();
	ObjectData GetData();
private:
	CircleCollider* myCircleCollider;
	Sprite mySprite;
	ObjectData myData;
};