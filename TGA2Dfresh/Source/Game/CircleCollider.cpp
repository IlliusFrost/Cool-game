#include "stdafx.h"
#include "CircleCollider.hpp"
#include "Player.hpp"
#include "Planet.hpp"
#include "Pickup.h"
#include <tga2d/engine.h>

CircleCollider::CircleCollider(Vector2f aPos, float aRadius, CollisionFlag aFlag, ObjectData* myData) :
	myPos	 (aPos),
	myRadius (aRadius),
	myObjectData(myData)
{
	myFlag = aFlag;
}

CircleCollider::~CircleCollider()
{
}

bool CircleCollider::CollidesWith(Vector2f aPoint)
{
	Vector2f delta = myPos - aPoint;
	delta.x /= Tga2D::CEngine::GetInstance()->GetWindowRatio() / 2;
	delta.y *= Tga2D::CEngine::GetInstance()->GetWindowRatioInversed();
	return delta.Length() < myRadius;
}

bool CircleCollider::CollidesWith(CircleCollider aCircle)
{
	Vector2f delta = myPos - aCircle.myPos;
	delta.x /= Tga2D::CEngine::GetInstance()->GetWindowRatio() / 2;
	delta.y *= Tga2D::CEngine::GetInstance()->GetWindowRatioInversed();
	return delta.Length() < (myRadius + aCircle.myRadius);
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