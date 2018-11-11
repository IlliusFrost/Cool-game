#pragma once
#include "State.h"

class StateStack;

class IntroState : public State
{
public:
	IntroState(StateStack* aStateStack, InputHandler* aInputHandler);
	~IntroState();

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
	Sprite myBG;
	float timer;
	float timerLength;
};
