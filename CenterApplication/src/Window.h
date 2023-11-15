#pragma once

#include "../resource.h"
#include "Settings.h"
#include <Windows.h>
#include <shellapi.h>
#include <strsafe.h>
#include <commctrl.h>
#include <winuser.h>
#include <iostream>

#define NOTIFICATION_TRAY_ICON_MSG (WM_USER + 0x001)
#define IDM_OPTIONS 100
#define IDM_EXIT 200

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void CenterApplicationOnFocus();
bool isFullscreen(HWND* appToCheck, MONITORINFO monitorInfo);
bool isMaximized(HWND* appToCheck);

class Window
{
public:
	// Constructor and destructor
	Window();
	~Window();

	// Make sure the window can't be copied
	Window(const Window&) = delete;
	void operator=(const Window&) = delete;

	// Loop throw messages
	bool MessageLoop();
private:
	// Instance of the window
	HINSTANCE m_hInstance;
	// Window
	HWND hWnd;
	// Notification
	NOTIFYICONDATA nid = {};
	// Settings
	Settings* settings;

	// Window's class
	const wchar_t* CLASS_NAME = L"Sample Window Class";

	// Create the notification icon
	void CreateShellNotification();

	// Center the app
	void CenterApplicationOnFocus();
};