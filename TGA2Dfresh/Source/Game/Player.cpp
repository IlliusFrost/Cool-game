
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
	myData.myPosition = aPosition;
	myData.mySprite = aSprite;
	myData.mySprite->SetPivot({ 0.5f,0.5f });

	myData.myGravityVelocity = { 0.f, 0.f };
	myData.myGravityVelocityCap = 0.025f;
	myData.myGravityVelocityIncrement = 0.001f;

	myData.myVelocityCap = 0.025f;
	myData.myVelocityIncrement = 0.001f;

	myCircleCollider = new CircleCollider(Vector2f(0.8f, 0.8f), 0.03f, CollisionFlag::ePlayer, &myData);
	myCircleCollider->SetCollisionEvent([this]()
	{
		//std::cout << "Player Collided with pickup and gained 5 mass! Player now has " << myMass << " mass." << std::endl;
		myMass += 5;
	}, CollisionFlag::ePickup);
	myCircleCollider->SetCollisionEvent([]()
	{
		//std::cout << "Player Collided with field!" << std::endl;
	}, CollisionFlag::eGravitationField);
	myCircleCollider->SetCollisionEvent([]()
	{
		//std::cout << "Player Collided with planet!" << std::endl;
	}, CollisionFlag::ePlanet);
	myCircleCollider->AddFlag(CollisionFlag::ePickup);
	myCircleCollider->AddFlag(CollisionFlag::ePlanet);
	myCircleCollider->AddFlag(CollisionFlag::eGravitationField);
	ColliderManager::GetInstance()->RegisterCollider(myCircleCollider);
}

Player::Player()
{

}
int Player::GetMass()
{
	return myData.myMass;
}

Vector2f Player::GetPosition()
{
	return myData.myPosition;
}

void Player::ModifyMass(int anAmountToModify)
{
	myData.myMass += anAmountToModify;
}


void Player::Update(InputHandler* anInputHandler, float aTimeDelta)
{
#ifndef _DEBUG
	myData.myVelocity += (anInputHandler->GetXboxLeftStick(0) / 10.0f) * aTimeDelta / 100.f;
#endif
	Vector2f delta = myData.myPosition - myData.myVelocity;

	if (myData.myVelocity.Length() < 0.1f)
	{
		if (anInputHandler->IsKeyDown(InputHandler::Keys::A))
		{
			myData.myVelocity.x -= myData.myVelocityIncrement * aTimeDelta / 3;

		}
		if (anInputHandler->IsKeyDown(InputHandler::Keys::D))
		{
			myData.myVelocity.x += myData.myVelocityIncrement * aTimeDelta / 3;
		}

		if (anInputHandler->IsKeyDown(InputHandler::Keys::S))
		{
			myData.myVelocity.y += myData.myVelocityIncrement * aTimeDelta / 3;
		}

		if (anInputHandler->IsKeyDown(InputHandler::Keys::W))
		{
			myData.myVelocity.y -= myData.myVelocityIncrement * aTimeDelta / 3;
		}
	}

	if (anInputHandler->IsKeyDown(InputHandler::Mouse::LeftMouseButton))
	{
		float mousePosX = static_cast<float>(anInputHandler->GetMousePosX()) / Tga2D::CEngine::GetInstance()->GetWindowSize().x;
		float mousePosY = static_cast<float>(anInputHandler->GetMousePosY()) / Tga2D::CEngine::GetInstance()->GetWindowSize().y;
		myData.myPosition = { mousePosX, mousePosY };
		myData.myVelocity = { 0.f, 0.f };
		myData.myGravityVelocity = { 0.f, 0.f };
	}

	//myVelocity.y -= 0.5f;
	if (myData.myVelocity.x > myData.myVelocityCap)
		myData.myVelocity.x = myData.myVelocityCap;
	if (myData.myVelocity.y > myData.myVelocityCap)
		myData.myVelocity.y = myData.myVelocityCap;
	if (myData.myGravityVelocity.x > myData.myVelocityCap)
		myData.myGravityVelocity.x = myData.myVelocityCap;
	if (myData.myGravityVelocity.y > myData.myVelocityCap)
		myData.myGravityVelocity.y = myData.myVelocityCap;
	if (myData.myVelocity.x < -myData.myVelocityCap)
		myData.myVelocity.x = -myData.myVelocityCap;
	if (myData.myVelocity.y < -myData.myVelocityCap)
		myData.myVelocity.y = -myData.myVelocityCap;
	if (myData.myGravityVelocity.x < -myData.myVelocityCap)
		myData.myGravityVelocity.x = -myData.myVelocityCap;
	if (myData.myGravityVelocity.y < -myData.myVelocityCap)
		myData.myGravityVelocity.y = -myData.myVelocityCap;

	myData.myPosition += myData.myVelocity;
	myData.myPosition += myData.myGravityVelocity;
	myData.mySprite->SetPosition({ myData.myPosition.x, myData.myPosition.y });
	myCircleCollider->SetPosition({ myData.myPosition.x, myData.myPosition.y});

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
	myData.mySprite->Render();
}