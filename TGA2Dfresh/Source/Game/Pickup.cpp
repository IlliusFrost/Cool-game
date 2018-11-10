#include "stdafx.h"
#include <iostream>
#include "Pickup.h"
#include "Player.hpp"
#include "ColliderManager.h"
void PickUp::Draw()
{
	mySprite->Render();
}
bool PickUp::GetIfIsRemoved()
{
	return isRemoved;
}
PickUp::~PickUp()
{
	SAFE_DELETE(myCircleCollider);
	SAFE_DELETE(mySprite);
}
PickUp::PickUp(Vector2f aPosition, Sprite aSprite)
{
	myPosition = aPosition;
	mySprite = aSprite;
	mySprite->SetPivot({ 0.5f, 0.5f });
	mySprite->SetPosition({ myPosition.x,myPosition.y });
	myCircleCollider = new CircleCollider(Vector2f(myPosition.x, myPosition.y), 0.1f, CollisionFlag::ePickup);
	myCircleCollider->SetCollisionEvent([this]() 
	{ 
		std::cout << "Pickup Collided with player, it was removed!" << std::endl; 
		isRemoved = true;
	}, CollisionFlag::ePlayer);
	myCircleCollider->AddFlag(CollisionFlag::ePlayer);
	ColliderManager::GetInstance()->RegisterCollider(myCircleCollider);
}
