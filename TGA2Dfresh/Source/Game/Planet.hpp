#pragma once
class CircleCollider;
class Planet
{
public:
	Planet(Vector2f aPos, Sprite aSprite);
	~Planet();
	void Update();
	void Render();


private:
	Vector2f myPos;
	CircleCollider* myCollider;
	int myMass;
	float myGravitationalPull;
	Sprite mySprite;
};