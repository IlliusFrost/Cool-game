
#include <..\CommonUtilities\InputHandler.hpp>
#include "stdafx.h"
#include <iostream>
#include "ColliderManager.h"
#include "Player.hpp"
#include "CircleCollider.hpp"


Player::Player(Vector2f aPosition, Sprite aSprite)
{
	myPosition = aPosition;
	mySprite = aSprite;
	mySprite->SetPivot({ 0.5f,0.5f });
	myCircleCollider = new CircleCollider(Vector2f(0.8f, 0.8f), 0.1f, CollisionFlag::ePlayer);
	myCircleCollider->SetCollisionEvent([]()
	{
		std::cout << "Player Collider!" << std::endl;
	});
	ColliderManager::GetInstance()->RegisterCollider(myCircleCollider);
}

Player::Player()
{

}
int Player::GetMass()
{
	return myMass;
}

Vector2f Player::GetPosition()
{
	return myPosition;
}

void Player::ModifyMass(int anAmountToModify)
{
	myMass += anAmountToModify;
}

void Player::Update(InputHandler* anInputHandler, float aTimeDelta)
{

	myVelocity += (anInputHandler->GetXboxLeftStick(0) / 100.0f) * aTimeDelta;
	if (anInputHandler->IsKeyDown(InputHandler::Keys::Left_Arrow))
	{
		myVelocity.x -= 0.1f * aTimeDelta;

	}
	else if (anInputHandler->IsKeyDown(InputHandler::Keys::Right_Arrow))
	{
		myVelocity.x += 0.1f * aTimeDelta;
	}

	if (anInputHandler->IsKeyDown(InputHandler::Keys::Spacebar))
	{
		myVelocity.y = 10;
	}

	//myVelocity.y -= 0.5f;
	myPosition += myVelocity;
	mySprite->SetPosition({ myPosition.x, myPosition.y });
	myCircleCollider->SetPosition({myPosition.x, myPosition.y});

	/*if (myVelocity.x >= 1)
	{
		myVelocity.x -= 0.001;
	}
	else if (myVelocity.x > 0 || myVelocity.x <0 && myVelocity.x > -1)
	{
		myVelocity.x = 0;
	}
	else if (myVelocity.x <= -1)
	{
		myVelocity.x += 0.001;
	}
	if (myVelocity.y >= 1)
	{
		myVelocity.y -= 0.001;
	}
	else if (myVelocity.y > 0 || myVelocity.y <0 && myVelocity.y > -1)
	{
		myVelocity.y = 0;
	}
	else if (myVelocity.y <= -1)
	{
		myVelocity.y += 0.001;
	}*/
}
void Player::Draw()
{
	mySprite->Render();
}