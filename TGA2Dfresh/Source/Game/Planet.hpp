#pragma once
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
	Vector2f myPos;
	CircleCollider* myCollider;
	int myMass;
	float myGravitationalPull;
	Sprite mySprite;
};