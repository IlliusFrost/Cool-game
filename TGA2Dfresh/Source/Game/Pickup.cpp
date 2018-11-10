#include "stdafx.h"
#include <iostream>
#include "Pickup.h"
#include "Player.hpp"
#include "ColliderManager.h"
void PickUp::Draw()
{
	myData.mySprite->Render();
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
		std::cout << "Pickup Collided with player!" << std::endl; 
		// ta bort pickup
	}, CollisionFlag::ePlayer);
	ColliderManager::GetInstance()->RegisterCollider(myCircleCollider);
}

void PickUp::OnPickUp(Player* aPlayerPickingUp)
{
	aPlayerPickingUp->ModifyMass(5);
	
}