#include "main.h"
#pragma comment(lib, "CallistoEngine.lib")

#include "ShooterGame.h"
#include "time.h"
#include "chrono"
#include <sstream>
#include "toml.hpp"
#include <iostream>

#if OPENGL
#include "Window_GL.h"
#endif

#if OPENGL	
double calculateDeltaTime(double& lastFrameTime)
{
	double temp_time = clock();
	double deltaTime = (temp_time - lastFrameTime) / CLOCKS_PER_SEC;
	lastFrameTime = temp_time;
	return deltaTime;
}

// this is part of the game
int main()
{
	toml::table config;
	try {

		config = toml::parse_file("Config/settings.toml");

	}
	catch (const toml::parse_error& err)
	{
		std::cerr
			<< "Error parsing file '" << err.source().path
			<< "':\n" << err.description()
			<< "\n (" << err.source().begin << ")\n";
		return 1;
	}

	// Accessing display settings
	auto display = config["settings"]["display"];
	std::string resolution = *display["resolution"].value<std::string>();
	bool fullscreen = *display["fullscreen"].value<bool>();

	std::cout << "Resolution: " << resolution << "\n";
	std::cout << "Fullscreen: " << (fullscreen ? "true" : "false") << "\n";

	// Splitting the resolution into width and height
	std::istringstream res_stream(resolution);
	std::string width_str, height_str;
	std::getline(res_stream, width_str, 'x');
	std::getline(res_stream, height_str, 'x');

	int width = std::stoi(width_str);
	int height = std::stoi(height_str);



	// Accessing controls settings
	auto controls = config["settings"]["controls"];
	std::string forward = *controls["move_forward"].value<std::string>();
	std::string backward = *controls["move_back"].value<std::string>();

	std::cout << "Forward key: " << forward << "\n";
	std::cout << "Backward key: " << backward << "\n";

	//table.for_each([](auto& key, auto& value)
	//	{
	//		std::cout << value << "\n";
	//		std::cout << key << "\n";
	//		//if constexpr (toml::is_string<decltype(value)>)
	//		//	//do_something_with_string_values(value);
	//	});



	double deltaTime = 0.0f;
	double lastFrameTime = 0.0f;
	float fps = 0.0f;
	int frameCount = 0;
	int lastFrameCount = 0;

	std::chrono::high_resolution_clock::time_point time = std::chrono::high_resolution_clock::now();

	Game* game;

	Window_GL* _window = new Window_GL(new ShooterGame(), width, height);

	_window->Initialise("Gamey game");

	game = _window->GetGame();
	game->Initialise(_window);


	while (game->IsRunning())
	{
		++frameCount;
		game->Run(deltaTime);
		_window->Update();

		deltaTime = calculateDeltaTime(lastFrameTime);
		auto newTime = std::chrono::high_resolution_clock::now();
		std::chrono::duration<float> time_span = std::chrono::duration_cast<std::chrono::duration<float>>(newTime - time);

		if (time_span.count() > 1.0f)
		{
			fps = frameCount - lastFrameCount;
			lastFrameCount = frameCount;
			time = newTime;
			//std::cout << "FPS: " << fps << std::endl;

			std::stringstream ss;
			ss << "Gamey game :: " << fps << " FPS";
			_window->SetTitle(ss.str().c_str());
		}
	}

	delete _window;
	return 0;
}
#endif
