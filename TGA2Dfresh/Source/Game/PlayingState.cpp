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
#include "UI.h"

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
	myPlayer1 = new Player(Vector2f(0.1f, 0.1f), new Tga2D::CSprite("sprites/PlayerOne.png"), 0);
	myPlayer2 = new Player(Vector2f(0.9f, 0.9f), new Tga2D::CSprite("sprites/PlayerTwo.png"), 1);
	myPlayer3 = new Player(Vector2f(0.1f, 0.9f), new Tga2D::CSprite("sprites/PlayerThree.png"), 2);
	myPlayer4 = new Player(Vector2f(0.9f, 0.1f), new Tga2D::CSprite("sprites/PlayerFour.png"), 3);
	myPickUpManager = new PickUpManager();
	myUIManager = new UIManager();
}

bool PlayState::Update(float aDeltaTime)
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		Tga2D::CEngine::Shutdown();
	}

	myPlayer1->Update(myInputHandler, aDeltaTime, myUIManager);
	myPlayer2->Update(myInputHandler, aDeltaTime, myUIManager);
	myPlayer3->Update(myInputHandler, aDeltaTime, myUIManager);
	myPlayer4->Update(myInputHandler, aDeltaTime, myUIManager);

	myPickUpManager->Update(aDeltaTime);
	myUIManager->Update();
	
	myPlanetManager->Update();
	myPlayer1->Draw();
	myPlayer2->Draw();
	myPlayer3->Draw();
	myPlayer4->Draw();
	if (myPlayer1->GetMass() >= 10 || myPlayer2->GetMass() >= 10 || myPlayer3->GetMass() >= 10 || myPlayer4->GetMass() >= 10)
	{
		if (gameSecondPhase == false)
		{
			gameSecondPhase = true;
			myPickUpManager->SecondPhase();
			myPlayer1->SecondPhase();
			myPlayer2->SecondPhase();
			myPlayer3->SecondPhase();
			myPlayer4->SecondPhase();
		}
		
	}
	//myPlanetManager->PrintPlanetsData();	
	myPickUpManager->Draw();
	ColliderManager::GetInstance()->Update(aDeltaTime);
	myUIManager->Draw();
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