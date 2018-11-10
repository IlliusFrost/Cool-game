
#include <..\CommonUtilities\InputHandler.hpp>
#include "stdafx.h"
#include <iostream>
#include "ColliderManager.h"
#include "Player.hpp"
#include "CircleCollider.hpp"


Player::Player(Vector2f aPosition, Sprite aSprite)
{
	myData.myPosition = aPosition;
	myData.mySprite = aSprite;
	myData.mySprite->SetPivot({ 0.5f,0.5f });

	myCircleCollider = new CircleCollider(Vector2f(0.8f, 0.8f), 0.1f, CollisionFlag::ePlayer, &myData);
	myCircleCollider->SetCollisionEvent([]()
	{
		std::cout << "Player Collided with pickup!" << std::endl;
		// myscore ++
	}, CollisionFlag::ePickup);
	myCircleCollider->SetCollisionEvent([]()
	{
		std::cout << "Player Collided with field!" << std::endl;
	}, CollisionFlag::eGravitationField);
	myCircleCollider->SetCollisionEvent([]()
	{
		std::cout << "Player Collided with planet!" << std::endl;
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

	//myData.myVelocity += (anInputHandler->GetXboxLeftStick(0) / 100.0f) * aTimeDelta;
	Vector2f delta = myData.myPosition - myData.myVelocity;

	if (myData.myVelocity.Length() < 0.1f)
	{
		if (anInputHandler->IsKeyDown(InputHandler::Keys::A))
		{
			myData.myVelocity.x -= 0.1f * aTimeDelta / 3;

		}
		else if (anInputHandler->IsKeyDown(InputHandler::Keys::D))
		{
			myData.myVelocity.x += 0.1f * aTimeDelta / 3;
		}

		else if (anInputHandler->IsKeyDown(InputHandler::Keys::S))
		{
			myData.myVelocity.y += 0.1f * aTimeDelta / 3;
		}

		else if (anInputHandler->IsKeyDown(InputHandler::Keys::W))
		{
			myData.myVelocity.y -= 0.1f * aTimeDelta / 3;
		}
	}

	if (anInputHandler->IsKeyDown(InputHandler::Keys::Spacebar))
	{
		myData.myPosition = { 0.5f, 0.5f };
	}

	if (anInputHandler->IsKeyDown(InputHandler::Mouse::LeftMouseButton))
	{
		float mousePosX = static_cast<float>(anInputHandler->GetMousePosX()) / Tga2D::CEngine::GetInstance()->GetWindowSize().x;
		float mousePosY = static_cast<float>(anInputHandler->GetMousePosY()) / Tga2D::CEngine::GetInstance()->GetWindowSize().y;
		myData.myPosition = { mousePosX, mousePosY };
		myData.myVelocity = { 0.f, 0.f };
	}

	//myVelocity.y -= 0.5f;
	myData.myPosition += myData.myVelocity;
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