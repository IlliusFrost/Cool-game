#pragma once
#include "stdafx.h"
#include <vector>

class PickUpManager
{
	friend class PickUp;
public:
	void Update(float aDeltaTime);
	void Draw();
	void DeletePickUp(int aPickUpIndex);
	void SpawnPickUp();
	PickUpManager();
	void SecondPhase();
private:
	std::vector<PickUp*> myPickUps = {};
	bool isSpawning = true;
	float mySpawnDelay = 0.5f;
	float mySpawnTimer = 0;
};