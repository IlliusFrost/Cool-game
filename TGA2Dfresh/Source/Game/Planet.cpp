#include "stdafx.h"
#include "Planet.hpp"
#include "CircleCollider.hpp"
#include "ColliderManager.h"

Planet::Planet()
{
}

Planet::~Planet()
{
	SAFE_DELETE(myPlanetData.mySprite);
}

void Planet::Init(const char* aString, Vector2f aPos)
{
	myPlanetData.mySprite = new Tga2D::CSprite(aString);
	myPlanetData.mySprite->SetPivot({ 0.5f, 0.5f });
	myPlanetData.myRadius = .041f;
	myPlanetData.myPosition = aPos;
	myFieldData.mySprite = new Tga2D::CSprite(aString);
	myFieldData.mySprite->SetPivot({ 0.5f, 0.5f });
	myFieldData.myRadius = .18f;
	myFieldData.myPosition = aPos;
	myCollider = new CircleCollider(myPlanetData.myPosition, myPlanetData.myRadius,CollisionFlag::ePlanet, &myPlanetData);
	myGravityCollider = new CircleCollider(myFieldData.myPosition, myFieldData.myRadius, CollisionFlag::eGravitationField, &myFieldData);

	ColliderManager::GetInstance()->RegisterCollider(myCollider);
	ColliderManager::GetInstance()->RegisterCollider(myGravityCollider);
	myPlanetData.mySprite->SetPosition({ myPlanetData.myPosition.x,myPlanetData.myPosition.y });
}
void Planet::Update()
{
	Draw();
}

void Planet::Draw()
{
	myPlanetData.mySprite->Render();
}

Vector2f Planet::GetPos()
{
	return myPlanetData.myPosition;
}