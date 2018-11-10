#include "stdafx.h"
#include "CircleCollider.hpp"
#include "Player.hpp"
#include "Planet.hpp"
#include "Pickup.h"

CircleCollider::CircleCollider(Vector2f aPos, float aRadius, CollisionFlag aFlag) : 
	myPos	 (aPos),
	myRadius (aRadius)
{
	myFlag = aFlag;
}

CircleCollider::~CircleCollider()
{
}

bool CircleCollider::CollidesWith(Vector2f aPoint)
{
	Vector2f delta = myPos - aPoint;
	return delta.Length() < myRadius;
}

bool CircleCollider::CollidesWith(CircleCollider aCircle)
{
	Vector2f delta = myPos - aCircle.myPos;
	return delta.Length() < myRadius + aCircle.myRadius;
}

void CircleCollider::SetCollisionEvent(std::function<void()> aFunc, CollisionFlag aFlag)
{
	myCollisionEvents[aFlag] = aFunc;
}

void CircleCollider::SetPosition(Vector2f aPos)
{
	myPos = aPos;
}

void CircleCollider::AddFlag(CollisionFlag aFlag)
{
	for (int i = 0; i < myCanCollideWith.size(); i++)
	{
		if (myCanCollideWith[i] == aFlag)
			return;
	}
	myCanCollideWith.push_back(aFlag);
}

void CircleCollider::CollisionEvent(CollisionFlag aFlag)
{
	myCollisionEvents[aFlag]();
}