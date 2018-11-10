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

CGameWorld::CGameWorld()
{
	myTga2dLogoSprite = nullptr;
}


CGameWorld::~CGameWorld() 
{
	SAFE_DELETE(myTga2dLogoSprite);
	//SAFE_DELETE(myStateStack);
	ColliderManager::Destroy();
	SAFE_DELETE(myTestPickUp);
	SAFE_DELETE(myPlanetManager);
}

void CGameWorld::Init(InputHandler* aInputHandler)
{
	ColliderManager::Create();
	ColliderManager::GetInstance()->Init();

	CircleCollider* collider1 = new CircleCollider(Vector2f(0.5f, 0.5f), 0.1f);
	CircleCollider* collider2 = new CircleCollider(Vector2f(0.3f, 0.5f), 0.1f);

	collider1->SetCollisionEvent([]() { std::cout << "<collider1> collided with <collider2>!" << std::endl; });
	collider2->SetCollisionEvent([]() { std::cout << "<collider2> collided with <collider1>!" << std::endl; });

	//ColliderManager::GetInstance()->RegisterCollider(collider1);
	//ColliderManager::GetInstance()->RegisterCollider(collider2);

	myStateStack = new StateStack();
	myStateStack->AddState(new PlayState(myStateStack), "Play");
	myStateStack->PushState("Play");

	myPlanetManager = new PlanetManager();
	myPlanetManager->InitPlanets();
	myInputHandler = aInputHandler;
	myTga2dLogoSprite = new Tga2D::CSprite("sprites/tga_logo.dds");
	myTga2dLogoSprite->SetPivot({ 0.5f, 0.5f });
	myTga2dLogoSprite->SetPosition({ 0.5f, 0.5f });

	myPlayer = new Player(Vector2f(0.1f, 0.1f), new Tga2D::CSprite("sprites/dude.png"));
	myTestPickUp = new PickUpManager();
	myPlayer = new Player(Vector2f(0.1f, 0.1f), new Tga2D::CSprite("sprites/dude.png"));
	myTestPickUp->SpawnPickUp();


	myPlayer = new Player(Vector2f(0.1f, 0.1f), new Tga2D::CSprite("sprites/dude.png"));
	myTestPickUp = new PickUpManager();
	myTestPickUp->SpawnPickUp();
}

void CGameWorld::Update(float aTimeDelta)
{
	aTimeDelta;
	myStateStack->Update(aTimeDelta);
	if (myInputHandler->IsKeyDown(InputHandler::Mouse::LeftMouseButton))
	{
		float mousePosX = static_cast<float>(myInputHandler->GetMousePosX()) / Tga2D::CEngine::GetInstance()->GetWindowSize().x;
		float mousePosY = static_cast<float>(myInputHandler->GetMousePosY()) / Tga2D::CEngine::GetInstance()->GetWindowSize().y;
		myTga2dLogoSprite->SetPosition({ mousePosX, mousePosY });
	}

	Vector2f leftstickVal = myInputHandler->GetXboxLeftStick(0) * aTimeDelta;
	leftstickVal += {myTga2dLogoSprite->GetPosition().x, myTga2dLogoSprite->GetPosition().y};
	myTga2dLogoSprite->SetPosition({ leftstickVal.x, leftstickVal.y });

	//std::cout << myInputHandler->GetXboxLeftStick(0).x << " : " << myInputHandler->GetXboxLeftStick(0).y << std::endl;

	if (GetAsyncKeyState(VK_ESCAPE))
	{
		Tga2D::CEngine::Shutdown();
	}
	myTga2dLogoSprite->Render();

	myPlayer->Update(myInputHandler, aTimeDelta);
	myPlayer->Draw();
	myPlanetManager->Update();
	//myPlanetManager->PrintPlanetsData();
	myTestPickUp->Draw();
	ColliderManager::GetInstance()->Update(aTimeDelta);
}