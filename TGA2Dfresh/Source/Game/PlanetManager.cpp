#include "stdafx.h"
#include "PlanetManager.hpp"
#include "Planet.hpp"
#include <iostream>
#include <string>
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
		
		myPlanets[i] = new Planet();
		myPlanets[i]->Init(mySpriteLocations[i].c_str(), myPlanetPositions[i]);
		std::cout << "Planet " << i + 1 << " PosX " << myPlanetPositions[i].x << " PosY " << myPlanetPositions[i].y << std::endl;
	}

}

void PlanetManager::Update()
{
	for (int i = 0; i < myPlanets.size(); i++)
	{
		myPlanets[i]->Update();
	}
}

void PlanetManager::PrintPlanetsData()
{
	for (int i = 0; i < myPlanets.size(); i++)
	{
		std::cout << "Planet" << i + 1 << " Sprite " << mySpriteLocations[i] << std::endl;
		std::cout << "Planet " << i + 1 << " PosX " << myPlanetPositions[i].x << " PosY " << myPlanetPositions[i].y << std::endl;
	}
}

