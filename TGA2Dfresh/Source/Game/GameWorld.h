#pragma once
#include "Player.hpp"
namespace Tga2D
{
	class CSprite;
}
class InputHandler;
class StateStack;

class CGameWorld
{
public:
	CGameWorld(); 
	~CGameWorld();

	void Init(InputHandler* aInputHandler);
	void Update(float aTimeDelta); 
private:
	Tga2D::CSprite* myTga2dLogoSprite;
	InputHandler* myInputHandler;
	StateStack* myStateStack;
	Player myPlayer;
};