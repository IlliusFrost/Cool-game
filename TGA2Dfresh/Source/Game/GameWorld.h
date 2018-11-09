#pragma once

namespace Tga2D
{
	class CSprite;
}
class Planet;
class InputHandler;

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
	Planet* myTestPlanet;
};