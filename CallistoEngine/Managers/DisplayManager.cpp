#include "DisplayManager.h"
#include "../TomlReader.h"

DisplayManager* DisplayManager::mInstance = nullptr;

void DisplayManager::LoadConfig(std::string pFilename)
{
	TomlReader reader;
	toml::table config = reader.ReadFile(pFilename.c_str());
	
	if(config.empty())
	{
		std::cerr << "DisplayManager :: Error parsing file\n";
		// setup some default values
		SetResolution(1280, 720);
		SetFullscreen(false);
		SetVSync(true);
		SetFov(90);
		SetCursorEnabled(true);

		return;
	}

	// Accessing display settings
	auto display = config["settings"]["display"];
	std::string resolution = *display["resolution"].value<std::string>();
	bool fullscreen = *display["fullscreen"].value<bool>();

	SetFullscreen(fullscreen);
	
	// Splitting the resolution into width and height
	std::istringstream res_stream(resolution);
	std::string width_str, height_str;
	std::getline(res_stream, width_str, 'x');
	std::getline(res_stream, height_str, 'x');

	SetResolution(std::stoi(width_str), std::stoi(height_str));

	SetVSync(*display["vsync"].value<bool>());
	SetFov(*display["fov"].value<int>());

	SetCursorEnabled(*display["cursor"].value<bool>());
}
