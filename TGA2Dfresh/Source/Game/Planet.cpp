#include "stdafx.h"
#include "Planet.hpp"
#include "CircleCollider.hpp"

Planet::Planet(Vector2f aPos, Sprite aSprite)
{
	myCollider = new CircleCollider();
	mySprite = aSprite;
	myPos = aPos;
	mySprite->SetPivot({ 0.5f, 0.5f });
	mySprite->SetPosition({ myPos.x, myPos.y });
}


Planet::~Planet()
{
	SAFE_DELETE(myCollider);
	SAFE_DELETE(mySprite);
}

void Planet::Update()
{
	Draw();
}

void Planet::Draw()
{
	mySprite->Render();
}

Vector2f Planet::GetPos()
{
	return myPos;
}

