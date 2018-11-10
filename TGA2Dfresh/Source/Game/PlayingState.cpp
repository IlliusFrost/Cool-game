#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/sprite/sprite.h>
#include <tga2d/error/error_manager.h>
#include <tga2d/engine.h>
#include <..\CommonUtilities\InputHandler.hpp>
#include "PlanetManager.hpp"
#include <iostream>
#include "Player.hpp"
#include "StateStack.h"
#include "ColliderManager.h"
#include "CircleCollider.hpp"
#include "Pickup.h"
#include "Planet.hpp"
#include "PlayingState.h"
#include "PickUpManager.h"

PlayState::PlayState(StateStack* aStateStack, InputHandler* aInputHandler)
{
	myStateStack = aStateStack;
	myInputHandler = aInputHandler;
}

PlayState::~PlayState()
{

}

void PlayState::Init()
{
	ColliderManager::Create();
	ColliderManager::GetInstance()->Init();

	myPlanetManager = new PlanetManager();
	myPlanetManager->InitPlanets();
	
	myTga2dLogoSprite = new Tga2D::CSprite("sprites/tga_logo.dds");
	myTga2dLogoSprite->SetPivot({ 0.5f, 0.5f });
	myTga2dLogoSprite->SetPosition({ 0.5f, 0.5f });

	myPlayer = new Player(Vector2f(0.1f, 0.1f), new Tga2D::CSprite("sprites/PlayerOne.png"));
	myTestPickUp = new PickUpManager();
	myTestPickUp->SpawnPickUp();
}

bool PlayState::Update(float aDeltaTime)
{
	/*if (myInputHandler->IsKeyDown(InputHandler::Mouse::LeftMouseButton))
	{
		float mousePosX = static_cast<float>(myInputHandler->GetMousePosX()) / Tga2D::CEngine::GetInstance()->GetWindowSize().x;
		float mousePosY = static_cast<float>(myInputHandler->GetMousePosY()) / Tga2D::CEngine::GetInstance()->GetWindowSize().y;
		myTga2dLogoSprite->SetPosition({ mousePosX, mousePosY });
	}

	Vector2f leftstickVal = myInputHandler->GetXboxLeftStick(0) * aDeltaTime;
	leftstickVal += {myTga2dLogoSprite->GetPosition().x, myTga2dLogoSprite->GetPosition().y};
	myTga2dLogoSprite->SetPosition({ leftstickVal.x, leftstickVal.y });*/

	//std::cout << myInputHandler->GetXboxLeftStick(0).x << " : " << myInputHandler->GetXboxLeftStick(0).y << std::endl;

	if (GetAsyncKeyState(VK_ESCAPE))
	{
		Tga2D::CEngine::Shutdown();
	}
	//myTga2dLogoSprite->Render();

	myPlayer->Update(myInputHandler, aDeltaTime);
	myPlayer->Draw();
	myPlanetManager->Update();
	//myPlanetManager->PrintPlanetsData();
	myTestPickUp->Update();
	myTestPickUp->Draw();
	ColliderManager::GetInstance()->Update(aDeltaTime);
	return true;
}

void PlayState::Enter()
{
	std::cout << "Entered PlayingState" << std::endl;
}

void PlayState::Exit()
{
	std::cout << "Exited PlayingState" << std::endl;
}

bool PlayState::PassThroughRender() const
{
	return false;
}

bool PlayState::PassThroughUpdate() const
{
	return false;
}