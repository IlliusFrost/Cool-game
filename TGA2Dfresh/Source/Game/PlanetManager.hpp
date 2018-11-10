#pragma once
#include <array>

class Planet;

class PlanetManager
{
public:
	PlanetManager();
	~PlanetManager();
	void InitPlanets();
	void Update();

private:
	std::array<Planet*, 5> myPlanets;
	const std::array<std::string, 5> mySpriteLocations = {"sprites/PlanetBlue.png", "sprites/PlanetGreen.png", "sprites/PlanetOrange.png", "sprites/PlanetPurple.png", "sprites/PlanetRed.png"};
	const std::array<Vector2f, 5> myPlanetPositions = {Vector2f(0.15f, 0.15f), Vector2f(0.3f, 0.3f) ,Vector2f(0.45f, 0.45f) ,Vector2f(0.60f, 0.60f) ,Vector2f(0.75f, 0.75f) };
};