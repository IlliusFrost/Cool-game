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
	PlayState(StateStack* aStateStack);
	~PlayState();

	void Init() override;
	bool Update(float aDeltaTime) override;
	void Enter() override;
	void Exit() override;
	bool PassThroughRender() const override;
	bool PassThroughUpdate() const override;
private:
	StateStack* myStateStack;

	Level myLevel;

	int myStartSplineIndex;
};

