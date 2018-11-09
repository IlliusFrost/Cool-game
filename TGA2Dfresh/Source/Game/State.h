#pragma once
class State
{
public:
	State();
	virtual ~State();

	virtual void Init() = 0;
	virtual bool Update(float aDt) = 0;
	virtual void Enter() = 0;
	virtual void Exit() = 0;
	virtual bool PassThroughRender() const = 0;
	virtual bool PassThroughUpdate() const = 0;

};

