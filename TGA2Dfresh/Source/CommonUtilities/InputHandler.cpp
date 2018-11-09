#include "stdafx.h"
#include "InputHandler.hpp"

InputHandler::InputHandler()
{
}


InputHandler::~InputHandler()
{
}

bool InputHandler::UpdateEvents(UINT aMessage, WPARAM aWparam, LPARAM aLparam)
{
	myPreviousKeyCodes = myKeyCodes;
	//myMouseWheelMovement = 0;
	/*myMouseMovement.x = 0;
	myMouseMovement.y = 0;*/
	switch (aMessage)
	{
	case WM_KEYDOWN:
		myKeyCodes.set(aWparam);
		break;
	case WM_KEYUP:
		myKeyCodes.reset(aWparam);
		break;
	case WM_LBUTTONDOWN:
		myKeyCodes.set(VK_LBUTTON);
		break;
	case WM_LBUTTONUP:
		myKeyCodes.reset(VK_LBUTTON);
		break;
	case WM_MBUTTONDOWN:
		myKeyCodes.set(VK_MBUTTON);
		break;
	case WM_MBUTTONUP:
		myKeyCodes.reset(VK_MBUTTON);
		break;
	case WM_RBUTTONDOWN:
		myKeyCodes.set(VK_RBUTTON);
		break;
	case WM_RBUTTONUP:
		myKeyCodes.reset(VK_RBUTTON);
		break;
	case WM_XBUTTONDOWN:
		if (GET_XBUTTON_WPARAM(aWparam) == 1)
		{
			myKeyCodes.set(VK_XBUTTON1);
		}
		else if (GET_XBUTTON_WPARAM(aWparam) == 2)
		{
			myKeyCodes.set(VK_XBUTTON2);
		}
		break;
	case WM_XBUTTONUP:
		if (GET_XBUTTON_WPARAM(aWparam) == 1)
		{
			myKeyCodes.reset(VK_XBUTTON1);
		}
		else if (GET_XBUTTON_WPARAM(aWparam) == 2)
		{
			myKeyCodes.reset(VK_XBUTTON2);
		}
		break;
	case WM_MOUSEWHEEL:
		myMouseWheelMovement = GET_WHEEL_DELTA_WPARAM(aWparam);

		if (myMouseWheelMovement > 0)
		{
			myMouseWheelMovement = 1;
		}
		else if (myMouseWheelMovement < 0)
		{
			myMouseWheelMovement = -1;
		}
		break;
	case WM_MOUSEMOVE:
		myMousePos.x = GET_X_LPARAM(aLparam);
		myMousePos.y = GET_Y_LPARAM(aLparam);
		UpdateMouseAbsolutePos();
		break;
	default:
		break;
	}
	return false;
}

bool InputHandler::IsKeyPressed(Keys aKey)
{
	return myPreviousKeyCodes[static_cast<int>(aKey)] == false && myKeyCodes[static_cast<int>(aKey)];
}

bool InputHandler::IsKeyPressed(Mouse aMouseKey)
{
	return myPreviousKeyCodes[static_cast<int>(aMouseKey)] == false && myKeyCodes[static_cast<int>(aMouseKey)];
}

bool InputHandler::IsKeyReleased(Keys aKey)
{
	return myPreviousKeyCodes[static_cast<int>(aKey)] && myKeyCodes[static_cast<int>(aKey)] == false;
}

bool InputHandler::IsKeyReleased(Mouse aMouseKey)
{
	return myPreviousKeyCodes[static_cast<int>(aMouseKey)] && myKeyCodes[static_cast<int>(aMouseKey)] == false;
}

bool InputHandler::IsKeyDown(Keys aKey)
{
	return myPreviousKeyCodes[static_cast<int>(aKey)] && myKeyCodes[static_cast<int>(aKey)];
}

bool InputHandler::IsKeyDown(Mouse aMouseKey)
{
	return myPreviousKeyCodes[static_cast<int>(aMouseKey)] && myKeyCodes[static_cast<int>(aMouseKey)];
}

int InputHandler::GetMouseWheelMovement() const
{
	return myMouseWheelMovement;
}

int InputHandler::GetMousePosX() const
{
	return myMousePos.x;
}

int InputHandler::GetMousePosY() const
{
	return myMousePos.y;
}

POINT InputHandler::GetMousePos() const
{
	return myMousePos;
}

void InputHandler::UpdateMouseAbsolutePos()
{
	GetCursorPos(&myMouseAbsolutePos);
}

POINT InputHandler::GetMouseAbsolutePos() const
{
	return myMouseAbsolutePos;
}

void InputHandler::SetMousePos(int aX, int aY)
{
	SetCursorPos(aX, aY);
}