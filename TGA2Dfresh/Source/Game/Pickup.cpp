#include "stdafx.h"
#include <iostream>
#include "Pickup.h"
#include "Player.hpp"
#include "ColliderManager.h"
void PickUp::Draw()
{
	myData.mySprite->Render();
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
CircleCollider* PickUp::GetCollider()
{
	return myCircleCollider;
}

PickUp::PickUp(Vector2f aPosition, Sprite aSprite)
{
	myData.myPosition = aPosition;
	myData.mySprite = aSprite;
	myData.mySprite->SetPivot({ 0.5f, 0.5f });
	myData.mySprite->SetPosition({ myData.myPosition.x,myData.myPosition.y });
	myCircleCollider = new CircleCollider(Vector2f(myData.myPosition.x, myData.myPosition.y), 0.1f, CollisionFlag::ePickup, &myData);
	myCircleCollider->SetCollisionEvent([this]() 
	{ 
		std::cout << "Pickup Collided with player, it was removed!" << std::endl; 
		isRemoved = true;
	}, CollisionFlag::ePlayer);
	myCircleCollider->AddFlag(CollisionFlag::ePlayer);
	ColliderManager::GetInstance()->RegisterCollider(myCircleCollider);
}
