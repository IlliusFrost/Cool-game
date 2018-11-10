#pragma once
#include "State.h"

class StateStack;
class Player;

enum class Level
{
	Level1,
	Level2,
	Level3
};
class InputHandler;
class StateStack;
class PickUpManager;
class Player;
class PlanetManager;
class Planet;
class PlayState : public State
{
public:
	enum class Level
	{
		Level0,
		Level1,
		Level2,
		Level3
	};
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
	Level myLevel;

	int myStartSplineIndex;

	Tga2D::CSprite* myTga2dLogoSprite;
	InputHandler* myInputHandler;
	StateStack* myStateStack;
	Player* myPlayer;
	PickUpManager* myTestPickUp;
	PlanetManager* myPlanetManager;
};

