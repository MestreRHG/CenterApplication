#include "Window.h"
#if _DEBUG
#else
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
	HANDLE m_singleInstanceMutex = CreateMutex(NULL, TRUE, L"WindowRecentered");
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		HWND existingApp = FindWindow(0, L"Window Recenter");
		if (existingApp)
		{
			SetForegroundWindow(existingApp);
			ShowWindow(existingApp, SW_SHOW);
		}
		return 1;
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