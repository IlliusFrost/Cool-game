#pragma once
#include "Collider.h"
#include "CollisionFlagEnum.h"

class CircleCollider : public Collider
{
	friend class ColliderManager;
public:
	CircleCollider(Vector2f aPos, float aRadius, CollisionFlag aFlag);
	~CircleCollider();
	bool CollidesWith(Vector2f aPoint) override;
	bool CollidesWith(CircleCollider aCircle) override;

	void SetCollisionEvent(std::function<void()> aFunc);
	void SetPosition(Vector2f aPos);
	void AddFlag(CollisionFlag aFlag);

private:
	void CollisionEvent() override;
	std::vector<CollisionFlag> myCanCollideWith;
	
	Vector2f myPos;
	float myRadius;
	std::function<void()> myCollisionEvent;
};
