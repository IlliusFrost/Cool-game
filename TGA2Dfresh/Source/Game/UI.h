#pragma once
#include "stdafx.h"
#include <vector>
namespace Tga2D
{
	class CSprite;
}

class UIManager
{
public:
	void Update();
	void Draw();
	UIManager();
	void SetPlayerScoreImage(int aPlayerScore, int aPlayerID);
private:
	std::vector<Sprite> myPlayerScoreSprites = {};
	std::vector<Sprite> myPlayerScoreOutput = {};
};