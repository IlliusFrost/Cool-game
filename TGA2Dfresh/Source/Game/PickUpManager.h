#pragma once
#include "stdafx.h"
#include <vector>
#include <tga2d/shaders/customshader.h>

class PickUpManager
{
	friend class PickUp;
public:
	PickUpManager(Tga2D::CCustomShader* aCustomShader);
	~PickUpManager();
	void Update(float aDeltaTime);
	void Draw();
	void DeletePickUp(int aPickUpIndex);
	void SpawnPickUp(Tga2D::CCustomShader* aCustomShader);
	PickUpManager();
	void SecondPhase();
private:
	std::vector<PickUp*> myPickUps = {};
	bool isSpawning = true;
	float mySpawnDelay = 0.5f;
	float mySpawnTimer = 0;
	Tga2D::CCustomShader* myCustomShader;
};