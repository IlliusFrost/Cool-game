#pragma once
#include "Collider.h"
#include "CollisionFlagEnum.h"
#include <unordered_map>
#include "GameObjectData.h"

class CircleCollider : public Collider
{
	friend class ColliderManager;
public:
	CircleCollider(Vector2f aPos, float aRadius, CollisionFlag aFlag, ObjectData* myData);
	~CircleCollider();
	bool CollidesWith(Vector2f aPoint) override;
	bool CollidesWith(CircleCollider aCircle) override;

	void SetCollisionEvent(std::function<void()> aFunc, CollisionFlag aFlag);
	void SetPosition(Vector2f aPos);
	void AddFlag(CollisionFlag aFlag);
	void SetRadius(float aNewRadius);
private:
	void CollisionEvent(CollisionFlag aFlag) override;
	std::vector<CollisionFlag> myCanCollideWith;
	
	ObjectData* myObjectData;

	Vector2f myPos;
	float myRadius;
	std::unordered_map<CollisionFlag, std::function<void()>> myCollisionEvents;
};
