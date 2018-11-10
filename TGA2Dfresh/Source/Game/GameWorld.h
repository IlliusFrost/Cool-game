#pragma once
namespace Tga2D
{
	class CSprite;
}
class InputHandler;
class StateStack;
class PickUp;
class Player;
class PlanetManager;
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
	//Planet* myTestPlanet;
	Player* myPlayer;
	PickUp* myTestPickUp;
	PlanetManager* myPlanetManager;
};