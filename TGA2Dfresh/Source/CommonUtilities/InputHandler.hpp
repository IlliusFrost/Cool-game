#pragma once
#include <Windows.h>
#include <Windowsx.h>
#include <WinUser.h>
#include <bitset>
#include <Xinput.h>
#include "Math/Vector2.hpp"
class InputHandler
{
public:
	InputHandler();
	~InputHandler();


	enum class Mouse
	{
		LeftMouseButton = VK_LBUTTON,
		RightMouseButton = VK_RBUTTON,
		MiddleMouseButton = VK_MBUTTON,
		Control_Break_Processing = VK_CANCEL,
		X1 = VK_XBUTTON1,
		X2 = VK_XBUTTON2,
	};
	enum class Keys
	{
		Backspace = VK_BACK,
		Tab = VK_TAB,
		Clear = VK_CLEAR,
		Enter = VK_RETURN,
		Shift = VK_SHIFT,
		Ctrl = VK_CONTROL,
		Control = VK_CONTROL,
		Alt = VK_MENU,
		Pause = VK_PAUSE,
		Caps_Lock = VK_CAPITAL,
		Kana_Mode = VK_KANA,
		Hanguel_Mode = VK_HANGUL,
		Hangul_Mode = VK_HANGUL,
		Junja_Mode = VK_JUNJA,
		Final_Mode = VK_FINAL,
		Hanja_Mode = VK_HANJA,
		Kanji_Mode = VK_KANJI,
		Mode_Kana = VK_KANA,
		Mode_Hanguel = VK_HANGUL,
		Mode_Hangul = VK_HANGUL,
		Mode_Junja = VK_JUNJA,
		Mode_Final = VK_FINAL,
		Mode_Hanja = VK_HANJA,
		Mode_Kanji = VK_KANJI,
		Esc = VK_ESCAPE,
		Escape = VK_ESCAPE,
		Escape_Key = VK_ESCAPE,
		IME_Convert = VK_CONVERT,
		IME_Nonconvert = VK_NONCONVERT,
		IME_Accept = VK_ACCEPT,
		IME_Mode_Change_Accept = VK_MODECHANGE,
		Space = VK_SPACE,
		Spacebar = VK_SPACE,
		Page_Up = VK_PRIOR,
		Page_Down = VK_NEXT,
		Pg_Up = VK_PRIOR,
		Pg_Dn = VK_NEXT,
		End = VK_END,
		Home = VK_HOME,
		Left_Arrow = VK_LEFT,
		Up_Arrow = VK_UP,
		Right_Arrow = VK_RIGHT,
		Down_Arrow = VK_DOWN,
		Select = VK_SELECT,
		Print = VK_PRINT,
		Execute = VK_EXECUTE,
		Print_Screen = VK_SNAPSHOT,
		Ins = VK_INSERT,
		Insert = VK_INSERT,
		Del = VK_DELETE,
		Delete = VK_DELETE,
		Help = VK_HELP,
		Number_0 = 0x30,
		Number_1 = 0x31,
		Number_2 = 0x32,
		Number_3 = 0x33,
		Number_4 = 0x34,
		Number_5 = 0x35,
		Number_6 = 0x36,
		Number_7 = 0x37,
		Number_8 = 0x38,
		Number_9 = 0x39,
		Letter_A = 0x41,
		Letter_B = 0x42,
		Letter_C = 0x43,
		Letter_D = 0x44,
		Letter_E = 0x45,
		Letter_F = 0x46,
		Letter_G = 0x47,
		Letter_H = 0x48,
		Letter_I = 0x49,
		Letter_J = 0x4A,
		Letter_K = 0x4B,
		Letter_L = 0x4C,
		Letter_M = 0x4D,
		Letter_N = 0x4E,
		Letter_O = 0x4F,
		Letter_P = 0x50,
		Letter_Q = 0x51,
		Letter_R = 0x52,
		Letter_S = 0x53,
		Letter_T = 0x54,
		Letter_U = 0x55,
		Letter_V = 0x56,
		Letter_W = 0x57,
		Letter_X = 0x58,
		Letter_Y = 0x59,
		Letter_Z = 0x5A,
		A = 0x41,
		B = 0x42,
		C = 0x43,
		D = 0x44,
		E = 0x45,
		F = 0x46,
		G = 0x47,
		H = 0x48,
		I = 0x49,
		J = 0x4A,
		K = 0x4B,
		L = 0x4C,
		M = 0x4D,
		N = 0x4E,
		O = 0x4F,
		P = 0x50,
		Q = 0x51,
		R = 0x52,
		S = 0x53,
		T = 0x54,
		U = 0x55,
		V = 0x56,
		W = 0x57,
		X = 0x58,
		Y = 0x59,
		Z = 0x5A,
		Windows_Key_Left = VK_LWIN,
		Windows_Key_Right = VK_RWIN,
		Applications = VK_APPS,
		Computer_Sleep = VK_SLEEP,
		Numeric_Keypad_0 = VK_NUMPAD0,
		Numeric_Keypad_1 = VK_NUMPAD1,
		Numeric_Keypad_2 = VK_NUMPAD2,
		Numeric_Keypad_3 = VK_NUMPAD3,
		Numeric_Keypad_4 = VK_NUMPAD4,
		Numeric_Keypad_5 = VK_NUMPAD5,
		Numeric_Keypad_6 = VK_NUMPAD6,
		Numeric_Keypad_7 = VK_NUMPAD7,
		Numeric_Keypad_8 = VK_NUMPAD8,
		Numeric_Keypad_9 = VK_NUMPAD9,
		NumPad_0 = VK_NUMPAD0,
		NumPad_1 = VK_NUMPAD1,
		NumPad_2 = VK_NUMPAD2,
		NumPad_3 = VK_NUMPAD3,
		NumPad_4 = VK_NUMPAD4,
		NumPad_5 = VK_NUMPAD5,
		NumPad_6 = VK_NUMPAD6,
		NumPad_7 = VK_NUMPAD7,
		NumPad_8 = VK_NUMPAD8,
		NumPad_9 = VK_NUMPAD9,
		Multiply = VK_MULTIPLY,
		Add = VK_ADD,
		Separator = VK_SEPARATOR,
		Subtract = VK_SUBTRACT,
		Decimal = VK_DECIMAL,
		Divide = VK_DIVIDE,
		F1 = VK_F1,
		F2 = VK_F2,
		F3 = VK_F3,
		F4 = VK_F4,
		F5 = VK_F5,
		F6 = VK_F6,
		F7 = VK_F7,
		F8 = VK_F8,
		F9 = VK_F9,
		F10 = VK_F10,
		F11 = VK_F11,
		F12 = VK_F12,
		F13 = VK_F13,
		F14 = VK_F14,
		F15 = VK_F15,
		F16 = VK_F16,
		F17 = VK_F17,
		F18 = VK_F18,
		F19 = VK_F19,
		F20 = VK_F20,
		F21 = VK_F21,
		F22 = VK_F22,
		F23 = VK_F23,
		F24 = VK_F24,
		Num_Lock = VK_NUMLOCK,
		Scroll_Lock = VK_SCROLL,
		Left_Shift = VK_LSHIFT,
		Right_Shift = VK_RSHIFT,
		Left_Ctrl = VK_LCONTROL,
		Right_Ctrl = VK_RCONTROL,
		Left_Menu = VK_LMENU,
		Right_Menu = VK_RMENU,
		Browser_Back = VK_BROWSER_BACK,
		Browser_Forward = VK_BROWSER_FORWARD,
		Browser_Refresh = VK_BROWSER_REFRESH,
		Browser_Stop = VK_BROWSER_STOP,
		Browser_Search = VK_BROWSER_SEARCH,
		Browser_Favourites = VK_BROWSER_FAVORITES,
		Browser_Start = VK_BROWSER_HOME,
		Browser_Home = VK_BROWSER_HOME,
		Volume_Mute = VK_VOLUME_MUTE,
		Volume_Down = VK_VOLUME_DOWN,
		Volume_Up = VK_VOLUME_UP,
		Next_Track = VK_MEDIA_NEXT_TRACK,
		Previous_Track = VK_MEDIA_PREV_TRACK,
		Stop_Media = VK_MEDIA_STOP,
		Play_Media = VK_MEDIA_PLAY_PAUSE,
		Pause_Media = VK_MEDIA_PLAY_PAUSE,
		Start_Mail = VK_LAUNCH_MAIL,
		Select_Media = VK_LAUNCH_MEDIA_SELECT,
		Start_Application_1 = VK_LAUNCH_APP1,
		Start_Application_2 = VK_LAUNCH_APP2,
		Semicolon_Key = VK_OEM_1,
		Colon_Key = VK_OEM_1,
		Plus_Key = VK_OEM_PLUS,
		Comma_Key = VK_OEM_COMMA,
		Dash_Key = VK_OEM_MINUS,
		Dot_Key = VK_OEM_PERIOD,
		Forward_Slash_Key = VK_OEM_2,
		Question_Mark_Key = VK_OEM_2,
		Apostrophe_Key = VK_OEM_3,
		Tilde_Key = VK_OEM_3,
		Bracket_Open_Key = VK_OEM_4,
		Curly_Bracket_Open_Key = VK_OEM_4,
		Back_Slash_Key = VK_OEM_5,
		Vertical_Bar_Key = VK_OEM_5,
		Bracket_Closed_Key = VK_OEM_6,
		Curly_Bracket_Closed_Key = VK_OEM_6,
		Single_Quote_Key = VK_OEM_7,
		Double_Quote_Key = VK_OEM_7,
		Misc_Characters = VK_OEM_8,
		Angle_Bracket_Key = VK_OEM_102,
		Back_Slash_Key_RT102 = VK_OEM_102,
		IME_Process = VK_PROCESSKEY,
		Packet = VK_PACKET,
		Attn = VK_ATTN,
		CrSel = VK_CRSEL,
		ExSel = VK_EXSEL,
		Erase_EOF = VK_EREOF,
		Play = VK_PLAY,
		Zoom = VK_ZOOM,
		PA1 = VK_PA1,
		Clear_Key = VK_OEM_CLEAR,
	};
	enum class XboxButton
	{
		DPadUp = 0x0001,
		DPadDown = 0x0002,
		DPadLeft = 0x0004,
		DPadRight = 0x0008,
		Start = 0x0010,
		Back = 0x0020,
		LeftThumb = 0x0040,
		RightThumb = 0x0080,
		LeftShoulder = 0x0100,
		RightShoulder = 0x0200,
		A = 0x1000,
		B = 0x2000,
		X = 0x4000,
		Y = 0x8000
	};

	bool UpdateEvents(UINT aMessage, WPARAM aWParam, LPARAM aLParam);
	void UpdateInputs();

	void CheckForControllers();

	bool XboxControllerIsConnected(int aController) const;
	int GetConnectedXboxControllers() const;

	void VibrateXboxController(float aAmount, int aController);
	void VibrateXboxController(float aLeftAmount, float aRightAmount, int aController);

	bool XboxDown(XboxButton aXboxButton, int aController) const;
	bool XboxPressed(XboxButton aXboxButton, int aController) const;
	bool XboxReleased(XboxButton aXboxButton, int aController) const;

	CommonUtilities::Vector2<float> GetXboxLeftStick(int aController) const;
	CommonUtilities::Vector2<float> GetXboxRightStick(int aController) const;
	float GetXboxLeftTrigger(int aController) const;
	float GetXboxRightTrigger(int aController) const;

	float GetXboxDeadzone() const;
	void SetXboxDeadzone(float aDeadzone);

	//Returns once if a keyboard or mouse key is pressed
	bool IsKeyPressed(Keys aKey);
	bool IsKeyPressed(Mouse aMouseKey);
	//Continously returns if a keyboard or mouse key is held down
	bool IsKeyDown(Keys aKey);
	bool IsKeyDown(Mouse aMouseKey);
	//Returns once if a keyboard or mouse key is released
	bool IsKeyReleased(Keys aKey);
	bool IsKeyReleased(Mouse aMouseKey);
	//Returns the mouse-wheels movement since last update
	int GetMouseWheelMovement() const;
	//Returns the current X position of the cursor
	int GetMousePosX() const;
	//Returns the current Y position of the cursor
	int GetMousePosY() const;
	//Returns the cursors position
	POINT GetMousePos() const;
	//Sets the cursors position to a the coordinates aX and aY
	void SetMousePos(int aX, int aY);

	POINT GetMouseAbsolutePos() const;

	void UpdateMouseAbsolutePos();

private:
	std::bitset<256> myKeyCodes;
	std::bitset<256> myPreviousKeyCodes;
	POINT myMousePos;
	POINT myMouseAbsolutePos;
	int myMouseWheelMovement;
	POINT p;
	std::bitset<XUSER_MAX_COUNT> myConnectedControllers;
	XINPUT_STATE myPreviousControllerStates[XUSER_MAX_COUNT];
	XINPUT_STATE myControllerStates[XUSER_MAX_COUNT];
	float myXboxDeadzone;
};