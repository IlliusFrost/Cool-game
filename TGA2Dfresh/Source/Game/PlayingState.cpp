#include "stdafx.h"
#include "PlayingState.h"
#include "StateStack.h"

PlayState::PlayState(StateStack* aStateStack)
{
	myStateStack = aStateStack;
}

PlayState::~PlayState()
{
}

void PlayState::Init()
{
}

bool PlayState::Update(float aDeltaTime)
{
	return true;
}

void PlayState::Enter()
{
	std::cout << "Entered PlayingState" << std::endl;
}

void PlayState::Exit()
{
	std::cout << "Exited PlayingState" << std::endl;
}

bool PlayState::PassThroughRender() const
{
	return false;
}

bool PlayState::PassThroughUpdate() const
{
	return false;
}