#include "stdafx.h"
#include <iostream>
#include "Pickup.h"
#include "Player.hpp"

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
}

void PickUp::OnPickUp(Player* aPlayerPickingUp)
{
	aPlayerPickingUp->ModifyMass(5);
	
}