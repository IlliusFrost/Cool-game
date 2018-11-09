#include "stdafx.h"
#include "GameWorld.h"
#include <tga2d/sprite/sprite.h>
#include <tga2d/error/error_manager.h>
#include <tga2d/engine.h>
#include <..\CommonUtilities\InputHandler.hpp>
#include "Planet.hpp"

CGameWorld::CGameWorld()
{
	myTga2dLogoSprite = nullptr;
	myTestPlanet = new Planet();
}


CGameWorld::~CGameWorld() 
{
	delete myTga2dLogoSprite;
	myTga2dLogoSprite = nullptr;
	myTestPlanet = nullptr;
}

void CGameWorld::Init(InputHandler* aInputHandler)
{
	myInputHandler = aInputHandler;
	myTga2dLogoSprite = new Tga2D::CSprite("sprites/tga_logo.dds");
	myTga2dLogoSprite->SetPivot({ 0.5f, 0.5f });
	myTga2dLogoSprite->SetPosition({ 0.5f, 0.5f });

	myTestPlanet->mySprite = new Tga2D::CSprite("sprites/PlanetRed.dds");
	myTestPlanet->mySprite->SetPivot({ 0.5f, 0.5f });
	myTestPlanet->mySprite->SetPosition({ 0.5f, 0.5f });
}


void CGameWorld::Update(float aTimeDelta)
{
	aTimeDelta;
	if (myInputHandler->IsKeyDown(InputHandler::Mouse::LeftMouseButton))
	{
		float mousePosX = static_cast<float>(myInputHandler->GetMousePosX()) / Tga2D::CEngine::GetInstance()->GetWindowSize().x;
		float mousePosY = static_cast<float>(myInputHandler->GetMousePosY()) / Tga2D::CEngine::GetInstance()->GetWindowSize().y;
		myTga2dLogoSprite->SetPosition({ mousePosX, mousePosY });
	}

	if (GetAsyncKeyState(VK_ESCAPE))
	{
		Tga2D::CEngine::Shutdown();
	}
	myTestPlanet->Render();
	//myTga2dLogoSprite->Render();
}