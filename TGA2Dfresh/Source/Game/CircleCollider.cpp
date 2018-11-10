#include "stdafx.h"
#include "CircleCollider.hpp"

CircleCollider::CircleCollider(Vector2f aPos, float aRadius)
	: 
	myPos	 (aPos),
	myRadius (aRadius)
{
	myCollisionEvent = []() {};
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

void CircleCollider::SetCollisionEvent(std::function<void()> aFunc)
{
	myCollisionEvent = aFunc;
}

void CircleCollider::SetPosition(Vector2f aPos)
{
	myPos = aPos;
}

void CircleCollider::CollisionEvent()
{
	myCollisionEvent();
}