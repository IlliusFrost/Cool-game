#pragma once
#include "State.h"

class InputHandler;
class StateStack;
class PickUpManager;
class Player;
class UIManager;
class PlayState : public State
{
public:
	PlayState(StateStack* aStateStack, InputHandler* aInputHandler);
	~PlayState();

	void Init() override;
	bool Update(float aDeltaTime) override;
	void Enter() override;
	void Exit() override;
	bool PassThroughRender() const override;
	bool PassThroughUpdate() const override;
private:
	Tga2D::CSprite* myTga2dLogoSprite;
	InputHandler* myInputHandler;
	StateStack* myStateStack;
	Player* myPlayer1;
	Player* myPlayer2;
	Player* myPlayer3;
	Player* myPlayer4;
	PickUpManager* myPickUpManager;
	PlanetManager* myPlanetManager;
	UIManager* myUIManager;
};
