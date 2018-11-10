#include "stdafx.h"
#include "Planet.hpp"
#include "CircleCollider.hpp"

Planet::Planet()
{

}



Planet::~Planet()
{
	SAFE_DELETE(myCollider);
	SAFE_DELETE(mySprite);
}

void Planet::Init(const char* aString, Vector2f aPos)
{
	mySprite = new Tga2D::CSprite(aString);
	mySprite->SetPivot({ 0.5f, 0.5f });
	mySprite->SetPosition({ myPos.x, myPos.y });
	myCollider = new CircleCollider();
	myPos = aPos;
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

