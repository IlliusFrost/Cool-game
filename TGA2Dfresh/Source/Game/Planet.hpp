#pragma once
class CircleCollider;
class Planet
{
public:
	Planet();
	~Planet();
	void Update();
	void Render();

	Sprite mySprite;

private:
	Vector2f myPos;
	CircleCollider* myCollider;
	int myMass;
	float myGravitationalPull;
};