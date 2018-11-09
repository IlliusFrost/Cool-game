#include "stdafx.h"
#include "Planet.hpp"
#include "CircleCollider.hpp"

Planet::Planet(Vector2f aPos, Sprite aSprite)
{
	myCollider = new CircleCollider();
	mySprite = aSprite;
	myPos = aPos;
}


Planet::~Planet()
{
	SAFE_DELETE(myCollider);
}

void Planet::Update()
{
	Render();
}

void Planet::Render()
{
	mySprite->Render();
}

