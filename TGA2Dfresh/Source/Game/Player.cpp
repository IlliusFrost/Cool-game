
#include <..\CommonUtilities\InputHandler.hpp>
#include "stdafx.h"
#include <iostream>
#include "ColliderManager.h"
#include "Player.hpp"
#include "CircleCollider.hpp"


Player::Player(Vector2f aPosition, Sprite aSprite, unsigned int aControlledID)
{
	myData.myControllerData = aControlledID;
	myData.myPosition = aPosition;
	myData.mySprite = aSprite;
	myData.mySprite->SetPivot({ 0.5f,0.5f });
	myData.mySprite->SetPivot({ 0.5f,0.5f });

	myData.myVelocityCap = 0.001f;
	myData.myVelocityIncrement = 0.001f;

	myCollider = new CircleCollider(Vector2f(0.8f, 0.8f), 0.020f, CollisionFlag::ePlayer, &myData);
	myCollider->SetCollisionEvent([this]()
	{
		//std::cout << "Player Collided with pickup and gained 5 mass! Player now has " << myMass << " mass." << std::endl;
	}, CollisionFlag::ePickup);
	myCollider->SetCollisionEvent([]()
	{
		//std::cout << "Player Collided with field!" << std::endl;
	}, CollisionFlag::eGravitationField);
	myCollider->SetCollisionEvent([this]()
	{
		//std::cout << "Player Collided with planet!" << std::endl;
		std::cout << "Player Collided with planet! and is grounded!" << std::endl;

	}, CollisionFlag::ePlanet);
	myCollider->SetCollisionEvent([this]()
	{
	}, CollisionFlag::ePlayer);
	myCollider->AddFlag(CollisionFlag::ePickup);
	myCollider->AddFlag(CollisionFlag::ePlanet);
	myCollider->AddFlag(CollisionFlag::eGravitationField);
	myCollider->AddFlag(CollisionFlag::ePlayer);
	ColliderManager::GetInstance()->RegisterCollider(myCollider);
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
	//myData.myVelocity += (anInputHandler->GetXboxLeftStick(0) / 10.0f) * aTimeDelta / 100.f;
#endif

	if (anInputHandler->IsKeyPressed(InputHandler::Keys::W) || anInputHandler->XboxPressed(InputHandler::XboxButton::A, myData.myControllerData))
	{
		myData.myVelocity.x += aTimeDelta * cosf(myData.mySprite->GetRotation()) * Tga2D::CEngine::GetInstance()->GetWindowRatioInversed();
		myData.myVelocity.y += aTimeDelta * sinf(myData.mySprite->GetRotation());

	}
	if (anInputHandler->IsKeyDown(InputHandler::Keys::A) || anInputHandler->GetXboxLeftStick(myData.myControllerData).x < 0.f)
	{
		myData.mySprite->SetRotation(myData.mySprite->GetRotation() - 10.f * aTimeDelta * anInputHandler->GetXboxLeftStick(myData.myControllerData).Length());
	}

	if (anInputHandler->IsKeyDown(InputHandler::Keys::D) || anInputHandler->GetXboxLeftStick(myData.myControllerData).x > 0.f)
	{
		myData.mySprite->SetRotation(myData.mySprite->GetRotation() + 10.f * aTimeDelta * anInputHandler->GetXboxLeftStick(myData.myControllerData).Length());
	}

	if (anInputHandler->IsKeyDown(InputHandler::Mouse::LeftMouseButton))
	{
		float mousePosX = static_cast<float>(anInputHandler->GetMousePosX()) / Tga2D::CEngine::GetInstance()->GetWindowSize().x;
		float mousePosY = static_cast<float>(anInputHandler->GetMousePosY()) / Tga2D::CEngine::GetInstance()->GetWindowSize().y;
		myData.myPosition = { mousePosX, mousePosY };
		myData.mySprite->SetPosition({ myData.myPosition.x, myData.myPosition.y });
		myCollider->SetPosition({ myData.myPosition.x, myData.myPosition.y });
		myData.myVelocity = { 0.f, 0.f };
	}

	if (myData.myPosition.x > 1.020f)
		myData.myPosition.x = -0.020f;
	if (myData.myPosition.y > 1.020f)
		myData.myPosition.y = -0.020f;
	if (myData.myPosition.x < -0.020f)
		myData.myPosition.x = 1.020f;
	if (myData.myPosition.y < -0.020f)
		myData.myPosition.y = 1.020f;

	myData.myPosition += myData.myVelocity;
	myData.myPosition += myData.myGravitationalVelocity;
	myData.mySprite->SetPosition({ myData.myPosition.x, myData.myPosition.y });
	myCollider->SetPosition({ myData.myPosition.x, myData.myPosition.y });
	myData.myVelocity.x *= 0.98f;
	myData.myVelocity.y *= 0.98f;
}

void Player::Draw()
{
	myData.mySprite->Render();
}