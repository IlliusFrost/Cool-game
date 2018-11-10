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
	ColliderManager::Destroy();
	SAFE_DELETE(myTga2dLogoSprite);
	SAFE_DELETE(myStateStack);
	SAFE_DELETE(myTestPickUp);
	SAFE_DELETE(myPlanetManager);
}

void CGameWorld::Init(InputHandler* aInputHandler)
{
	myStateStack = new StateStack();
	myStateStack->AddState(new PlayState(myStateStack, aInputHandler), "Play");
	myStateStack->PushState("Play");
}

void CGameWorld::Update(float aTimeDelta)
{
	myStateStack->Update(aTimeDelta);
}