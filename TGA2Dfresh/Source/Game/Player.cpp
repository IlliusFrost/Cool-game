
#include <..\CommonUtilities\InputHandler.hpp>
#include "stdafx.h"
#include <iostream>
#include "ColliderManager.h"
#include "Player.hpp"
#include "UI.h"
#include "CircleCollider.hpp"


Player::Player(Vector2f aPosition, Sprite aSprite, unsigned int aControlledID)
{
	myData.myControllerData = aControlledID;
	myData.myPosition = aPosition;
	myData.mySprite = aSprite;
	myData.mySprite->SetPivot({ 0.5f,0.5f });

	myData.myVelocityCap = 0.001f;
	myData.myVelocityIncrement = 0.001f;

	myCollider = new CircleCollider(Vector2f(0.8f, 0.8f), 0.020f, CollisionFlag::ePlayer, &myData);
	myCollider->SetCollisionEvent([this]()
	{
		ModifyMass(1);
	}, CollisionFlag::ePickup);
	myCollider->SetCollisionEvent([]()
	{
	}, CollisionFlag::eGravitationField);
	myCollider->SetCollisionEvent([this]()
	{
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
	if (myData.myMass > 10)
	{
		myData.myMass = 10;
	}
}
void Player::SecondPhase()
{
	isInSecondPhase = true;
}

void Player::Update(InputHandler* anInputHandler, float aTimeDelta, UIManager* aUIManager)
{
	if (isAlive || !isInSecondPhase)
	{
		if (anInputHandler->IsKeyPressed(InputHandler::Keys::W) || anInputHandler->XboxPressed(InputHandler::XboxButton::A, myData.myControllerData))
		{
			myData.myVelocity.x += aTimeDelta * cosf(myData.mySprite->GetRotation()) * Tga2D::CEngine::GetInstance()->GetWindowRatioInversed();
			myData.myVelocity.y += aTimeDelta * sinf(myData.mySprite->GetRotation());
		}
		myData.mySprite->SetRotation((std::atan2(anInputHandler->GetXboxLeftStick(myData.myControllerData).x, anInputHandler->GetXboxLeftStick(myData.myControllerData).y) - 3.14f / 2) * -1);
		/*if (anInputHandler->IsKeyDown(InputHandler::Keys::A) || anInputHandler->GetXboxLeftStick(myData.myControllerData).x < 0.f)
		{
			myData.mySprite->SetRotation(myData.mySprite->GetRotation() - 10.f * aTimeDelta * anInputHandler->GetXboxLeftStick(myData.myControllerData).Length());
		}*/

		aUIManager->SetPlayerScoreImage(myData.myMass, myData.myControllerData);

		/*if (anInputHandler->IsKeyDown(InputHandler::Keys::D) || anInputHandler->GetXboxLeftStick(myData.myControllerData).x > 0.f)
		{
			myData.mySprite->SetRotation(myData.mySprite->GetRotation() + 10.f * aTimeDelta * anInputHandler->GetXboxLeftStick(myData.myControllerData).Length());
		}*/

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
		{
			if (!isInSecondPhase)
			{
				myData.myPosition.x = -0.020f;
			}
			else
			{
				isAlive = false;
			}
		}

		if (myData.myPosition.y > 1.020f)
		{
			if (!isInSecondPhase)
			{
				myData.myPosition.y = -0.020f;
			}
			else
			{
				isAlive = false;
			}
		}

		if (myData.myPosition.x < -0.020f)
		{
			if (!isInSecondPhase)
			{
				myData.myPosition.x = 1.020f;
			}
			else
			{
				isAlive = false;
			}
		}

		if (myData.myPosition.y < -0.020f)
		{
			if (!isInSecondPhase)
			{
				myData.myPosition.y = 1.020f;
			}
			else
			{
				isAlive = false;
			}
		}
	}

	myData.myPosition += myData.myVelocity;
	myData.myPosition += myData.myGravitationalVelocity;
	myData.mySprite->SetPosition({ myData.myPosition.x, myData.myPosition.y });
	myCollider->SetPosition({ myData.myPosition.x, myData.myPosition.y });
	myData.myVelocity.x *= 0.993f;
	myData.myVelocity.y *= 0.993f;
}

void Player::Draw()
{
	myData.mySprite->Render();
}