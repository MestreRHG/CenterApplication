#include "Window.h"
#if _DEBUG
#else
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

int main()
{
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