#pragma once
#include <tga2d/Engine.h>
#include <fstream>
#include "GameWorld.h"
#include <..\CommonUtilities\InputHandler.hpp>
#include <..\CommonUtilities\Timer.hpp>

class CGame
{
public:
	CGame();
	~CGame();
	bool Init(const std::wstring& aVersion = L"", HWND aHWND = nullptr);
private:
	LRESULT WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void InitCallBack();
	void UpdateCallBack();


	CGameWorld myGameWorld;
	InputHandler myInputHandler;
	Timer myTimer;
};
