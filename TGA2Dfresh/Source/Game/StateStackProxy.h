#pragma once
class State;
class StateStack;
class StateStackProxy
{
public:
	StateStackProxy(StateStack& aStateStack);
	~StateStackProxy();

	void PushState(const std::string &aStateId) const;
	void PopAndPushState(const std::string &aStateId) const;

private:
	StateStack& myStateStack;
};

