#pragma once
#include "stdafx.h"
#include <vector>

class PickUpManager
{
	friend class PickUp;
public:
	void Update();
	void Draw();
	void DeletePickUp(int aPickUpIndex);
	void SpawnPickUp(Vector2f aPosition);
	PickUpManager();
private:
	std::vector<PickUp*> myPickUps = {};
	bool isDoneLooping = false;
};