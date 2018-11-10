#include "stdafx.h"
#include <iostream>
#include "Pickup.h"
#include "Player.hpp"
#include "ColliderManager.h"
void PickUp::Draw()
{
	mySprite->Render();
}

PickUp::PickUp(Vector2f aPosition, Sprite aSprite)
{
	myPosition = aPosition;
	mySprite = aSprite;
	mySprite->SetPivot({ 0.5f, 0.5f });
	mySprite->SetPosition({ myPosition.x,myPosition.y });
	myCircleCollider = new CircleCollider(Vector2f(0.5f, 0.5f), 0.1f, CollisionFlag::ePickup);
	myCircleCollider->SetCollisionEvent([]() 
	{ 
		std::cout << "Pickup Collider!" << std::endl; 
	});
	ColliderManager::GetInstance()->RegisterCollider(myCircleCollider);
}

void PickUp::OnPickUp(Player* aPlayerPickingUp)
{
	aPlayerPickingUp->ModifyMass(5);
	
}