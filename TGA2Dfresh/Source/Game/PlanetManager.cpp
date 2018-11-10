#include "stdafx.h"
#include "PlanetManager.hpp"
#include "Planet.hpp"

PlanetManager::PlanetManager()
{

}

PlanetManager::~PlanetManager()
{
	for (int i = 0; i < myPlanets.size(); i++)
	{
		SAFE_DELETE(myPlanets[i]);
	}
}

void PlanetManager::InitPlanets()
{
	for (int i = 0; i < myPlanets.size(); i++)
	{
		myPlanets[i] = new Planet(myPlanetPositions[i], myPlanetSprites[i]);
	}
}

void PlanetManager::Update()
{
	for (int i = 0; i < myPlanets.size(); i++)
	{
		myPlanets[i]->Update();
	}
}

