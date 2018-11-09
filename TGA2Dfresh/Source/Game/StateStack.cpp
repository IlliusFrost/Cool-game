#include "stdafx.h"
#include "State.h"
#include "StateStack.h"


StateStack::StateStack() :
	myStateStack(0),
	myPopQueue(0)
{
}


StateStack::~StateStack()
{
	std::map<std::string, State*>::iterator itr(myStates.begin());

	while (itr != myStates.end())
	{
		SAFE_DELETE(itr->second);
		++itr;
	}
}

void StateStack::AddState(State * aState, const std::string &aStateId)
{
	assert(myStates.find(aStateId) == myStates.end() && "State Id already in use");
	aState->Init();
	myStates.insert(std::pair<std::string, State*>(aStateId, aState));
}

State* StateStack::PushState(const std::string &aStateId)
{
	std::map<std::string, State*>::iterator itr = myStates.begin();
	itr = myStates.find(aStateId);

	assert(itr != myStates.end() && "State Id not found");

	myPushQueue.push(itr->second);

	return itr->second;
}

void StateStack::PopState()
{
	++myPopQueue;
}
void StateStack::ClearStack()
{
	myPopQueue += myStateStack.Size();
}
bool StateStack::Update(float aDeltaTime)
{
	while (myPopQueue > 0)
		PopStateInternal();
	while (myPushQueue.size() > 0)
		PushState();

	if (myStateStack.Size() == 0)
		return false;

	if (!UpdateAtIndex(myStateStack.Size() - 1, aDeltaTime))
		PopState();

	return (myStateStack.Size() > 0);
}

void StateStack::PushState()
{
	if (!(myPushQueue.size() > 0))
		return;

	if (myStateStack.Size() > 0)
		myStateStack.GetLast()->Exit();

	State* state = myPushQueue.front();
	myPushQueue.pop();

	state->Enter();

	myStateStack.Add(state);
}

void StateStack::PopStateInternal()
{
	assert(myStateStack.Size() > 0 && "Cannot pop empty stack");

	myStateStack.GetLast()->Exit();
	myStateStack.RemoveCyclicAtIndex(myStateStack.Size() - 1);

	if (myStateStack.Size() > 0)
		myStateStack.GetLast()->Enter();

	--myPopQueue;
}

bool StateStack::UpdateAtIndex(const uint32_t aIndex, float aDeltaTime)
{
	if (aIndex < 0)
		return false;

	if (myStateStack[aIndex]->PassThroughUpdate())
		UpdateAtIndex(aIndex - 1, aDeltaTime);

	return myStateStack[aIndex]->Update(aDeltaTime);
}
