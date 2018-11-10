#pragma once
namespace Tga2D
{
	class CSprite;
}
class InputHandler;
class StateStack;
class PickUpManager;
class Player;
class PlanetManager;
class Planet;
class PlayState;
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
	Player* myPlayer;
	PickUpManager* myTestPickUp;
	PlanetManager* myPlanetManager;
};