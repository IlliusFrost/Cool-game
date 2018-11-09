
#include <..\CommonUtilities\InputHandler.hpp>
#include "stdafx.h"
#include "Player.hpp"


Player::Player(Vector2f aPosition, Tga2D::CSprite* aSprite)
{
	myPosition = aPosition;
	mySprite = aSprite;
}

Player::Player()
{

}

void Player::Update(InputHandler* anInputHandler)
{
	if (anInputHandler->IsKeyDown(InputHandler::Keys::Left_Arrow))
	{
		myPosition.x -= 0.001f;

	}
	else if (anInputHandler->IsKeyDown(InputHandler::Keys::Right_Arrow))
	{
		myPosition.x += 0.001f;
	}
	mySprite->SetPosition({ myPosition.x, myPosition.y });
}
void Player::Draw()
{
	mySprite->Render();
}