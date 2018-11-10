#pragma once
class CircleCollider;

class Collider
{
public:
	Collider();
	~Collider();

	virtual bool CollidesWith(CircleCollider aCircle);
	virtual bool CollidesWith(Vector2f aPoint);

	virtual void CollisionEvent();

private:
};

