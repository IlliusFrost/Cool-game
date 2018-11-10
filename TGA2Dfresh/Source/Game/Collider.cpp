#include "stdafx.h"
#include "Collider.h"
#include "CircleCollider.hpp"

Collider::Collider()
{
}


Collider::~Collider()
{
}

bool Collider::CollidesWith(CircleCollider aCircle)
{
	aCircle;
	return false;
}

bool Collider::CollidesWith(Vector2f aPoint)
{
	aPoint;
	return false;
}

void Collider::CollisionEvent(CollisionFlag aFlag)
{
}
