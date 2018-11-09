#include "stdafx.h"
#include "Planet.hpp"
#include "CircleCollider.hpp"

Planet::Planet()
{
	myCollider = new CircleCollider();
	mySprite = nullptr;
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

