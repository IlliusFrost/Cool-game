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
	myPickUpManager->SpawnPickUp(Vector2f{0.2f,0.2f});
	myPickUpManager->SpawnPickUp(Vector2f{0.3f,0.3f});
	myPickUpManager->SpawnPickUp(Vector2f{0.4f,0.4f});
	myPickUpManager->SpawnPickUp(Vector2f{ 0.5f,0.4f });
	myPickUpManager->SpawnPickUp(Vector2f{ 0.6f,0.2f });
	myPickUpManager->SpawnPickUp(Vector2f{ 0.7f,0.8f });
	myUIManager = new UIManager();
}

bool PlayState::Update(float aDeltaTime)
{
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		Tga2D::CEngine::Shutdown();
	}

	myPlayer1->Update(myInputHandler, aDeltaTime, myUIManager);
	myPlayer1->Draw();
	myPlayer2->Update(myInputHandler, aDeltaTime, myUIManager);
	myPlayer2->Draw();
	myPlayer3->Update(myInputHandler, aDeltaTime, myUIManager);
	myPlayer3->Draw();
	myPlayer4->Update(myInputHandler, aDeltaTime, myUIManager);
	myPlayer4->Draw();
	myPlanetManager->Update();
	//myPlanetManager->PrintPlanetsData();
	myPickUpManager->Update(aDeltaTime);
	myPickUpManager->Draw();
	ColliderManager::GetInstance()->Update(aDeltaTime);
	myUIManager->Update();
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