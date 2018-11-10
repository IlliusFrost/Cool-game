#pragma once
#include "GameObjectData.h"
class CircleCollider;

class Planet
{
public:
	friend class PlanetManager;
	Planet();
	~Planet();
	void Init(const char* aString, Vector2f aPos);
	void Update();
	void Draw();
	Vector2f GetPos();

private:
	ObjectData myPlanetData;
	CircleCollider* myCollider;
	ObjectData myFieldData;
	CircleCollider* myGravityCollider;
};