#include "Settings.h"

Settings::Settings(const std::string& pathName)
{
	// Save the path
	path = pathName;

	// Open the file
	std::fstream settings;
	std::cout << "Now opening: " << path << '\n';
	settings.open(path);

	// If the file doesn't exist create one
	if (!settings)
	{
		std::cout << "File: " << path << " doesn't exist!\n";
		WriteDefault();
	}
	settings.close();
}

// In case there are no settings saved, create default
void Settings::WriteDefault()
{
	std::ofstream settingsOutput{ path };

	settingsOutput << "MonitorMode:" << (int)MonitorMode::bothMonitors	<< std::endl;
	settingsOutput << "ShortcutKey:" << (int)Keybind::VK_B				<< std::endl;

	settingsOutput.close();
}

void Settings::Read()
{
	std::fstream settings;
	settings.open(path);

	std::string s;
	int line = 0;

	while (settings)
	{
		std::getline(settings, s);
		size_t pos = s.find(":");
		if (pos != std::string::npos)
		{
			s = s.substr(pos + 1);
		}

		switch (line)
		{
			// Monitor mode
		case 0:
			std::cout << "Monitor mode = " << s << '\n';
			if (s == "0")
				monitorMode = (int)MonitorMode::bothMonitors;
			else if(s == "1")
				monitorMode = (int)MonitorMode::onlyPrimary;
			else
			{
				std::cout << "Error reading the value of monitor mode!";
				monitorMode = (int)MonitorMode::bothMonitors;
			}
			break;
			// KeyBind
		case 1:
			std::cout << "Shortcut key = " << s << '\n';
			break;
		default:
			break;
		}
		line++;
	}
	settings.close();
}

void Settings::Write()
{

}