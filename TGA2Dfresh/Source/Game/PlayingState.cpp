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
}

void PlayState::Enter()
{
}

void PlayState::Exit()
{
}

bool PlayState::PassThroughRender() const
{
	return false;
}

bool PlayState::PassThroughUpdate() const
{
	return false;
}