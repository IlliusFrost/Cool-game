#pragma once

#include <queue>
#include <map>

class State;
class StateStack
{
public:
	StateStack();
	~StateStack();

	void AddState(State* aState, const std::string &aStateId);
	State* PushState(const std::string &aStateId);
	void PopState();
	void ClearStack();
	bool Update(float aDeltaTime);

private:
	void PushState();
	void PopStateInternal();
	bool UpdateAtIndex(const uint32_t aIndex, float aDeltaTime);
	std::map<std::string, State*> myStates;

	GrowingArray<State*> myStateStack;

	std::queue<State*> myPushQueue;
	
	uint32_t myPopQueue;
};

