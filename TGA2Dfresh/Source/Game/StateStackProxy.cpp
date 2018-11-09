#include "stdafx.h"
#include "StateStack.h"
#include "StateStackProxy.h"


StateStackProxy::StateStackProxy(StateStack& aStateStack) :
	myStateStack(aStateStack)
{
}


StateStackProxy::~StateStackProxy()
{
}

void StateStackProxy::PushState(const std::string & aStateId) const
{
	myStateStack.PushState(aStateId);
}

void StateStackProxy::PopAndPushState(const std::string & aStateId) const
{
	myStateStack.PopState();
	myStateStack.PushState(aStateId);
}
