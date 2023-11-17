#pragma once
#include <String>
#include <iostream>
#include <fstream>

const enum class MonitorMode {
	bothMonitors = 0,
	onlyPrimary = 1
};

const enum class Keybind {
	// Keyboard
	VK_SHIFT		= 0x10,	// SHIFT key
	VK_CONTROL		= 0x11,	// CTRL key
	VK_MENU			= 0x12,	// ALT key
	VK_PAUSE		= 0x13,	// PAUSE key
	VK_SPACE		= 0x20,	// SPACEBAR
	VK_PRIOR		= 0x21,	// PAGE UP key
	VK_NEXT			= 0x22,	// PAGE DOWN key
	VK_END			= 0x23,	// END key
	VK_HOME			= 0x24,	// HOME key
	VK_LEFT			= 0x25,	// LEFT ARROW key
	VK_UP			= 0x26,	// UP ARROW key
	VK_RIGHT		= 0x27,	// RIGHT ARROW key
	VK_DOWN			= 0x28,	// DOWN ARROW key
	VK_0			= 0x30,	// 0 key
	VK_1			= 0x31,	// 1 key
	VK_2			= 0x32,	// 2 key
	VK_3			= 0x33,	// 3 key
	VK_4			= 0x34,	// 4 key
	VK_5			= 0x35,	// 5 key
	VK_6			= 0x36,	// 6 key
	VK_7			= 0x37,	// 7 key
	VK_8			= 0x38,	// 8 key
	VK_9			= 0x39,	// 9 key
	VK_A			= 0x41,	// A key
	VK_B			= 0x42,	// B key
	VK_C			= 0x43,	// C key
	VK_D			= 0x44,	// D key
	VK_E			= 0x45,	// E key
	VK_F			= 0x46,	// F key
	VK_G			= 0x47,	// G key
	VK_H			= 0x48,	// H key
	VK_I			= 0x49,	// I key
	VK_J			= 0x4A,	// J key
	VK_K			= 0x4B,	// K key
	VK_L			= 0x4C,	// L key
	VK_M			= 0x4D,	// M key
	VK_N			= 0x4E,	// N key
	VK_O			= 0x4F,	// O key
	VK_P			= 0x50,	// P key
	VK_Q			= 0x51,	// Q key
	VK_R			= 0x52,	// R key
	VK_S			= 0x53,	// S key
	VK_T			= 0x54,	// T key
	VK_U			= 0x55,	// U key
	VK_V			= 0x56,	// V key
	VK_W			= 0x57,	// W key
	VK_X			= 0x58,	// X key
	VK_Y			= 0x59,	// Y key
	VK_Z			= 0x5A,	// Z key

	// Numeric Keypad
	VK_NUMPAD0		= 0x60,	// Numeric keypad 0 key
	VK_NUMPAD1		= 0x61,	// Numeric keypad 1 key
	VK_NUMPAD2		= 0x62,	// Numeric keypad 2 key
	VK_NUMPAD3		= 0x63,	// Numeric keypad 3 key
	VK_NUMPAD4		= 0x64,	// Numeric keypad 4 key
	VK_NUMPAD5		= 0x65,	// Numeric keypad 5 key
	VK_NUMPAD6		= 0x66,	// Numeric keypad 6 key
	VK_NUMPAD7		= 0x67,	// Numeric keypad 7 key
	VK_NUMPAD8		= 0x68,	// Numeric keypad 8 key
	VK_NUMPAD9		= 0x69,	// Numeric keypad 9 key
	VK_MULTIPLY		= 0x6A,	// Multiply key
	VK_ADD			= 0x6B,	// Add key
	VK_SEPARATOR	= 0x6C,	// Separator key
	VK_SUBTRACT		= 0x6D,	// Subtract key
	VK_DECIMAL		= 0x6E,	// Decimal key
	VK_DIVIDE		= 0x6F,	// Divide key

	// Function keys
	VK_F1			= 0x70,	// F1 key
	VK_F2			= 0x71,	// F2 key
	VK_F3			= 0x72,	// F3 key
	VK_F4			= 0x73,	// F4 key
	VK_F5			= 0x74,	// F5 key
	VK_F6			= 0x75,	// F6 key
	VK_F7			= 0x76,	// F7 key
	VK_F8			= 0x77,	// F8 key
	VK_F9			= 0x78,	// F9 key
	VK_F10			= 0x79,	// F10 key
	VK_F11			= 0x7A,	// F11 key
	VK_F12			= 0x7B,	// F12 key
	VK_F13			= 0x7C,	// F13 key
	VK_F14			= 0x7D,	// F14 key
	VK_F15			= 0x7E,	// F15 key
	VK_F16			= 0x7F,	// F16 key
	VK_F17			= 0x80,	// F17 key
	VK_F18			= 0x81,	// F18 key
	VK_F19			= 0x82,	// F19 key
	VK_F20			= 0x83,	// F20 key
	VK_F21			= 0x84,	// F21 key
	VK_F22			= 0x85,	// F22 key
	VK_F23			= 0x86,	// F23 key
	VK_F24			= 0x87,	// F24 key
};

class Settings {
// Class functions
public:
	Settings(const std::string& pathName);

	Settings(const Settings&) = delete;
	void operator=(const Settings&) = delete;

// Read and Write
public:
	// Write setting
	void Write();
	// Read settings
	void Read();

// Settings read
public:
	// 0 - Use both monitors
	// 1 - Use only primary
	int monitorMode;
	// Key used in combination with ALT to center the focused app
	int keyBind;

// Other functions
private:
	// Write default settings
	void WriteDefault();

	std::string path;
};