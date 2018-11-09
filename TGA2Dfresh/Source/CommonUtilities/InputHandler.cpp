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

void InputHandler::UpdateInputs()
{
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		if (myConnectedControllers[i])
		{
			XINPUT_STATE state;
			ZeroMemory(&state, sizeof(XINPUT_STATE));

			dwResult = XInputGetState(i, &state);

			if (dwResult == ERROR_SUCCESS)
			{
				//if (state.dwPacketNumber != myControllerStates[i].dwPacketNumber)
				//{
				myPreviousControllerStates[i] = myControllerStates[i];
				myControllerStates[i] = state;
				//}
			}
			else
			{
				myConnectedControllers[i] = false;
			}
		}
	}
}

void InputHandler::CheckForControllers()
{
	DWORD dwResult;
	for (DWORD i = 0; i < XUSER_MAX_COUNT; i++)
	{
		XINPUT_STATE state;
		ZeroMemory(&state, sizeof(XINPUT_STATE));

		dwResult = XInputGetState(i, &state);

		if (dwResult == ERROR_SUCCESS)
		{
			//Controller is connected
			myConnectedControllers[i] = true;
			myControllerStates[i] = state;
		}
		else
		{
			myConnectedControllers[i] = false;
		}
	}
}

bool InputHandler::XboxControllerIsConnected(int aController) const
{
	return myConnectedControllers[aController];
}

int InputHandler::GetConnectedXboxControllers() const
{
	return static_cast<int>(myConnectedControllers.count());
}

void InputHandler::VibrateXboxController(float aAmount, int aController)
{
	VibrateXboxController(aAmount, aAmount, aController);
}

void InputHandler::VibrateXboxController(float aLeftAmount, float aRightAmount, int aController)
{
	assert(aController >= 0 && aController < XUSER_MAX_COUNT && "Controller index out of bounds.");
	if (XboxControllerIsConnected(aController))
	{
		aLeftAmount = __min(1.0f, __max(0.0f, aLeftAmount));
		aRightAmount = __min(1.0f, __max(0.0f, aRightAmount));
		XINPUT_VIBRATION vibration;
		ZeroMemory(&vibration, sizeof(XINPUT_VIBRATION));
		vibration.wLeftMotorSpeed = static_cast<WORD>(65535.0f * aLeftAmount);
		vibration.wRightMotorSpeed = static_cast<WORD>(65535.0f * aRightAmount);
		XInputSetState(aController, &vibration);
	}
}

bool InputHandler::XboxDown(XboxButton aXboxButton, int aController) const
{
	assert(aController >= 0 && aController < XUSER_MAX_COUNT && "Controller index out of bounds.");
	return XboxControllerIsConnected(aController) &&
		myControllerStates[aController].Gamepad.wButtons & static_cast<WORD>(aXboxButton);
}

bool InputHandler::XboxPressed(XboxButton aXboxButton, int aController) const
{
	assert(aController >= 0 && aController < XUSER_MAX_COUNT && "Controller index out of bounds.");
	return XboxControllerIsConnected(aController) &&
		myControllerStates[aController].Gamepad.wButtons & static_cast<WORD>(aXboxButton) &&
		!(myPreviousControllerStates[aController].Gamepad.wButtons & static_cast<WORD>(aXboxButton));
}

bool InputHandler::XboxReleased(XboxButton aXboxButton, int aController) const
{
	assert(aController >= 0 && aController < XUSER_MAX_COUNT && "Controller index out of bounds.");
	return XboxControllerIsConnected(aController) &&
		!(myControllerStates[aController].Gamepad.wButtons & static_cast<WORD>(aXboxButton)) &&
		myPreviousControllerStates[aController].Gamepad.wButtons & static_cast<WORD>(aXboxButton);
}

CommonUtilities::Vector2<float> InputHandler::GetXboxLeftStick(int aController) const
{
	CommonUtilities::Vector2<float> result;
	if (XboxControllerIsConnected(aController))
	{
		result = { static_cast<float>(myControllerStates[aController].Gamepad.sThumbLX / 32757.0f),
			static_cast<float>(myControllerStates[aController].Gamepad.sThumbLY / 32757.0f) };

		if (result.x != 0.0f)
			result.x = (result.x / abs(result.x)) * (__min(1.0f, __max(0.0f, abs(result.x) - myXboxDeadzone) / (1.0f - myXboxDeadzone)));
		if (result.y != 0.0f)
			result.y = -(result.y / abs(result.y)) * (__min(1.0f, __max(0.0f, abs(result.y) - myXboxDeadzone) / (1.0f - myXboxDeadzone)));
	}
	return result;
}

CommonUtilities::Vector2<float> InputHandler::GetXboxRightStick(int aController) const
{
	CommonUtilities::Vector2<float> result;
	if (XboxControllerIsConnected(aController))
	{
		result = { static_cast<float>(myControllerStates[aController].Gamepad.sThumbRX / 32757.0f),
			static_cast<float>(myControllerStates[aController].Gamepad.sThumbRY / 32757.0f) };
		result.x = (result.x / abs(result.x)) * (__min(1.0f, __max(0.0f, abs(result.x) - myXboxDeadzone) / (1.0f - myXboxDeadzone)));
		result.y = -(result.y / abs(result.y)) * (__min(1.0f, __max(0.0f, abs(result.y) - myXboxDeadzone) / (1.0f - myXboxDeadzone)));
	}
	return result;
}

float InputHandler::GetXboxLeftTrigger(int aController) const
{
	if (!XboxControllerIsConnected(aController)) { return 0.0f; }
	return static_cast<float>(myControllerStates[aController].Gamepad.bLeftTrigger) / 255.0f;
}

float InputHandler::GetXboxRightTrigger(int aController) const
{
	if (!XboxControllerIsConnected(aController)) { return 0.0f; }
	return static_cast<float>(myControllerStates[aController].Gamepad.bRightTrigger) / 255.0f;
}

float InputHandler::GetXboxDeadzone() const
{
	return myXboxDeadzone;
}

void InputHandler::SetXboxDeadzone(float aDeadzone)
{
	myXboxDeadzone = aDeadzone;
}

POINT InputHandler::GetMouseAbsolutePos() const
{
	return myMouseAbsolutePos;
}

void InputHandler::SetMousePos(int aX, int aY)
{
	SetCursorPos(aX, aY);
}