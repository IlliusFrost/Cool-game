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
	void OnPickUp(Player* aPlayerPickingUp);
	PickUp(Vector2f aPosition, Sprite aSprite);
	PickUp();
private:
	Vector2f myPosition;
	CircleCollider* myCollider;
	Sprite mySprite;
};