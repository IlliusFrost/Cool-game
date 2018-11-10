#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
	friend class ColliderManager;
public:
	CircleCollider(Vector2f aPos, float aRadius);
	~CircleCollider();
	bool CollidesWith(Vector2f aPoint) override;
	bool CollidesWith(CircleCollider aCircle) override;

	void SetCollisionEvent(std::function<void()> aFunc);
	void SetPosition(Vector2f aPos);

private:
	void CollisionEvent() override;
	
	Vector2f myPos;
	float myRadius;
	std::function<void()> myCollisionEvent;
};
