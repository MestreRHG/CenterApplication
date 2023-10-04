#include "Window.h"
#if _DEBUG
#else
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
	// Create a mutex to see if the app is already running
	HANDLE m_singleInstanceMutex = CreateMutex(NULL, TRUE, L"WindowRecentered");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		// Get the window, show it and bring it to focus
		HWND existingApp = FindWindow(0, L"Window Recenter");
		if (existingApp)
		{
			SetForegroundWindow(existingApp);
			ShowWindow(existingApp, SW_SHOW);
		}
		return 0;
	}

	std::cout << "Creating Window\n";

	// Pointer to a new window
	Window* pWindow = new Window();

	// Loop
	bool running = true;
	while (running)
	{
		if (!pWindow->MessageLoop())
		{
			std::cout << "Closing Window\n";
			running = false;
		}
		// Used so the window doesn't overload the computer
		Sleep(10);
	}
	delete pWindow;

	return 0;
}