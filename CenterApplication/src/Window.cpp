#include "Window.h"

// TODO
// Add options

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	// Close the window
	case WM_CLOSE:
		/*DestroyWindow(hWnd);*/
		ShowWindow(hWnd, SW_HIDE);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	// If the user right clicks the icon, create the menu
	case NOTIFICATION_TRAY_ICON_MSG:
	{
		switch (LOWORD(lParam))
		{
		case WM_CONTEXTMENU:
		{
			// Get cursor position
			POINT pt;
			GetCursorPos(&pt);

			// Create the menu and it's options
			HMENU hmenu = CreatePopupMenu();
			InsertMenu(hmenu, 0, MF_BYPOSITION | MF_STRING, IDM_OPTIONS, L"Options");
			InsertMenu(hmenu, 1, MF_SEPARATOR, 150, L"Separator");
			InsertMenu(hmenu, 2, MF_BYPOSITION | MF_STRING, IDM_EXIT, L"Exit");

			// Bring the app to focus
			SetForegroundWindow(hWnd);

			// Create the menu at mouse's position
			TrackPopupMenu(hmenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_BOTTOMALIGN, pt.x, pt.y, 0, hWnd, NULL);

			PostMessage(hWnd, WM_NULL, 0, 0);
			break;
		}
		}
		return 0;
	}
	// Read the menu's messages
	case WM_COMMAND:
		// Show the window that will later include options (maybe)
		if (wParam == IDM_OPTIONS)
		{
			ShowWindow(hWnd, SW_SHOW);
		}
		// Exit the application
		if (wParam == IDM_EXIT)
		{
			DestroyWindow(hWnd);
			return 0;
		}
		break;

	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window() : m_hInstance(GetModuleHandle(nullptr))
{
	// Create window class
	WNDCLASS wc = { };
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = m_hInstance;
	wc.lpszClassName = CLASS_NAME;

	// Register window class
	RegisterClass(&wc);

	// Create the window
	hWnd = CreateWindowEx(
		0,                              // Optional window styles.
		CLASS_NAME,                     // Window class
		L"Window Recenter",             // Window text
		WS_OVERLAPPEDWINDOW,            // Window style

		// Size and position
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

		NULL,                           // Parent window    
		NULL,                           // Menu
		m_hInstance,                    // Instance handle
		NULL                            // Additional application data
	);

	// Create the notification icon
	CreateShellNotification();

	// Read the settings file
	settings = new Settings("./settings.ini");
	settings->Read();

	// Hide the window
	ShowWindow(hWnd, SW_HIDE);
}

Window::~Window()
{
	delete settings;
	Shell_NotifyIcon(NIM_DELETE, &nid);
	UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::MessageLoop()
{
	// Register the shortcut
	if (RegisterHotKey(hWnd, 1, MOD_ALT | MOD_NOREPEAT, (int)Keybind::VK_B))
	{
		std::cout << "Hotkey 'ALT+b' registered, using MOD_NOREPEAT flag\n";
	}

	// Check messages
	MSG msg = { };
	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE))
	{
		// Check if user quit application
		if (msg.message == WM_QUIT)
			return false;
		// Check if the shortcut was used
		if (msg.message == WM_HOTKEY)
		{
			std::cout << "WM_HOTKEY received\n";
			CenterApplicationOnFocus();
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return true;
}

void Window::CreateShellNotification()
{
	// Create the notification information
	nid.cbSize = sizeof(nid);
	nid.hWnd = hWnd;
	nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP | NIF_SHOWTIP;
	nid.uCallbackMessage = NOTIFICATION_TRAY_ICON_MSG;
	nid.uVersion = NOTIFYICON_VERSION_4;

	// Notification ID
	static const GUID myGUID =
	{ 0x23977b55, 0x10e0, 0x4041, {0xb8, 0x62, 0xb1, 0x95, 0x41, 0x96, 0x36, 0x69} };
	nid.guidItem = myGUID;

	// Notification tooltip
	StringCchCopy(nid.szTip, ARRAYSIZE(nid.szTip), L"Recenter Application");

	// Load the notification icon
	nid.hIcon = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_ICON));

	// Show the notification
	if (Shell_NotifyIcon(NIM_ADD, &nid))
		Shell_NotifyIcon(NIM_SETVERSION, &nid);
}

void CenterApplicationOnFocus()
{
	// Get the window that's on focus
	HWND focusApp = GetForegroundWindow();
	if (focusApp == NULL)
		return;

	// Get monitor info
	MONITORINFO monitorInfo = { 0 };
	monitorInfo.cbSize = sizeof(MONITORINFO);
	GetMonitorInfo(MonitorFromWindow(focusApp, MONITOR_DEFAULTTOPRIMARY), &monitorInfo);

	// Check to see if application is maximized
	if (isMaximized(&focusApp))
		return;

	// Check if window is fullscreen
	if (isFullscreen(&focusApp, monitorInfo))
		return;

	// Get the center position
	RECT rectWindow;
	GetWindowRect(focusApp, &rectWindow);
	int posx, posy;
	posx = (monitorInfo.rcWork.left + monitorInfo.rcWork.right) / 2 - (rectWindow.right - rectWindow.left) / 2;
	posy = (monitorInfo.rcWork.top + monitorInfo.rcWork.bottom) / 2 - (rectWindow.bottom - rectWindow.top) / 2;

	MoveWindow(focusApp, posx, posy, rectWindow.right - rectWindow.left, rectWindow.bottom - rectWindow.top, TRUE);
}

bool isMaximized(HWND* appToCheck)
{
	// Get the placement of the window
	WINDOWPLACEMENT appPlacement = {};
	if (GetWindowPlacement(*appToCheck, &appPlacement) == 0)
	{
		std::cout << "Error getting window placement: " << GetLastError() << "\n";
		return true;
	}

	// Check if window is maximized
	if (appPlacement.showCmd == SW_MAXIMIZE)
	{
		std::cout << "Window is maximized\n";
		return true;
	}

	return false;
}

bool isFullscreen(HWND* appToCheck, MONITORINFO monitorInfo)
{
	// Now get the windows size
	RECT windowRect;
	GetWindowRect(*appToCheck, &windowRect);

	// If the window's size is equal to the size of the monitor, it's fullscreen
	if (windowRect.left == monitorInfo.rcMonitor.left
		&& windowRect.right == monitorInfo.rcMonitor.right
		&& windowRect.top == monitorInfo.rcMonitor.top
		&& windowRect.bottom == monitorInfo.rcMonitor.bottom)
	{
		std::cout << "Window is fullscreen\n";
		return true;
	}
	return false;
}