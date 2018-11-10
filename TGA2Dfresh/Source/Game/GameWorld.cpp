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

CGameWorld::CGameWorld()
{
	myTga2dLogoSprite = nullptr;
}


CGameWorld::~CGameWorld() 
{
	SAFE_DELETE(myTga2dLogoSprite);
	SAFE_DELETE(myStateStack);
	ColliderManager::Destroy();
	SAFE_DELETE(myTestPickUp);
	SAFE_DELETE(myPlanetManager);
}

void CGameWorld::Init(InputHandler* aInputHandler)
{
	ColliderManager::Create();
	ColliderManager::GetInstance()->Init();

	CircleCollider* collider1 = new CircleCollider(Vector2f( 0.5f, 0.5f ), 0.1f);
	CircleCollider* collider2 = new CircleCollider(Vector2f(0.3f, 0.5f), 0.1f);

	collider1->SetCollisionEvent([]() { std::cout << "<collider1> collided with <collider2>!" << std::endl; });
	collider2->SetCollisionEvent([]() { std::cout << "<collider1> collided with <collider2>!" << std::endl; });

	ColliderManager::GetInstance()->RegisterCollider(collider1);
	ColliderManager::GetInstance()->RegisterCollider(collider2);

	myStateStack = new StateStack();

	myPlanetManager = new PlanetManager();
	myPlanetManager->InitPlanets();
	myInputHandler = aInputHandler;
	myTga2dLogoSprite = new Tga2D::CSprite("sprites/tga_logo.dds");
	myTga2dLogoSprite->SetPivot({ 0.5f, 0.5f });
	myTga2dLogoSprite->SetPosition({ 0.5f, 0.5f });
	myPlayer = new Player(Vector2f(0.1f, 0.1f), new Tga2D::CSprite("sprites/dude.png"));
	myTestPickUp = new PickUp(Vector2f(0.5f, 0.5f), new Tga2D::CSprite("sprites/power.png"));



void CGameWorld::Update(float aTimeDelta)
{
	aTimeDelta;
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
	myTestPickUp->Draw();
	myPlanetManager->Update();
	myPlanetManager->PrintPlanetsData();
	ColliderManager::GetInstance()->Update(aTimeDelta);
}