
#include <..\CommonUtilities\InputHandler.hpp>
#include "stdafx.h"
#include <iostream>
#include "ColliderManager.h"
#include "Player.hpp"
#include "UI.h"
#include "CircleCollider.hpp"


Player::Player(Vector2f aPosition, Sprite aSprite)
{
	myData.myPosition = aPosition;
	myData.mySprite = aSprite;
	myData.mySprite->SetPivot({ 0.5f,0.5f });
	myData.myPosition = aPosition;
	myData.mySprite = aSprite;
	myData.mySprite->SetPivot({ 0.5f,0.5f });

	myData.myGravityVelocity = { 0.f, 0.f };
	myData.myGravityVelocityCap = 0.025f;
	myData.myGravityVelocityIncrement = 0.001f;

	myData.myVelocityCap = 0.025f;
	myData.myVelocityIncrement = 0.001f;

	myCircleCollider = new CircleCollider(Vector2f(0.8f, 0.8f), 0.020f, CollisionFlag::ePlayer, &myData);
	myCircleCollider->SetCollisionEvent([this]()
	{
		ModifyMass(1);
	}, CollisionFlag::ePickup);
	myCircleCollider->SetCollisionEvent([]()
	{
	}, CollisionFlag::eGravitationField);
	myCircleCollider->SetCollisionEvent([this]()
	{

		myData.isGrounded = true;
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
	std::cout << anAmountToModify << " " << myData.myMass;
}


void Player::Update(InputHandler* anInputHandler, float aTimeDelta, UIManager* aUIManager)
{
#ifndef _DEBUG
	if (myData.isGrounded)
	{
		myData.myVelocity += (anInputHandler->GetXboxLeftStick(0) / 10.0f) * aTimeDelta / 100.f;
	}
#endif

	aUIManager->SetPlayerScoreImage(myData.myMass);

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

		if (anInputHandler->XboxPressed(InputHandler::XboxButton::A,0) && myData.isGrounded == true)
		{
			Vector2f jumpVector = (myData.myPosition - myData.latestCollideObjectPosition);
			jumpVector = jumpVector.GetNormalized();
			jumpVector = { jumpVector.x / 100,jumpVector.y / 100 };
			myData.myVelocity += jumpVector;
			myData.isGrounded = false;
			std::cout << "Player is no longer grounded!" << std::endl;
		}
	}

	if (anInputHandler->IsKeyDown(InputHandler::Mouse::LeftMouseButton))
	{
		float mousePosX = static_cast<float>(anInputHandler->GetMousePosX()) / Tga2D::CEngine::GetInstance()->GetWindowSize().x;
		float mousePosY = static_cast<float>(anInputHandler->GetMousePosY()) / Tga2D::CEngine::GetInstance()->GetWindowSize().y;
		myData.myPosition = { mousePosX, mousePosY };
		myData.mySprite->SetPosition({ myData.myPosition.x, myData.myPosition.y });
		myCircleCollider->SetPosition({ myData.myPosition.x, myData.myPosition.y });
		myData.myVelocity = { 0.f, 0.f };
		myData.myGravityVelocity = { 0.f, 0.f };
		myData.isGrounded = false;
	}
	

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
			myCircleCollider->SetPosition({ myData.myPosition.x, myData.myPosition.y });
	
}
void Player::Draw()
{
	myData.mySprite->Render();
}