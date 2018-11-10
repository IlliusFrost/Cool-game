#pragma once
#include "CollisionFlagEnum.h"
class CircleCollider;

class Collider
{
public:
	Collider();
	~Collider();

	virtual bool CollidesWith(CircleCollider aCircle) = 0;
	virtual bool CollidesWith(Vector2f aPoint) = 0;

	virtual void CollisionEvent() = 0;
protected:
	CollisionFlag myFlag;
};

