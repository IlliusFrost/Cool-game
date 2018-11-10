#pragma once
#include <tga2d/sprite/sprite.h>
#include "CircleCollider.hpp"
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
	Vector2f myPosition;
	CircleCollider* myCircleCollider;
	Sprite mySprite;
	bool isRemoved = false; 
};