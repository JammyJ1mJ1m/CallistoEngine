#include "GameInputManager.h"
#include "../GameCommands/GameCommands.h"
#include "toml.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

GameInputManager::GameInputManager()
{
	mWKeyCommand = new MoveForwardCommand();
	mSKeyCommand = new MoveBackCommand();
	mAKeyCommand = new MoveLeftCommand();
	mDKeyCommand = new MoveRightCommand();

	// Initialize default commands
	mCommandMap["move_forward"] = mWKeyCommand;
	mCommandMap["move_back"] = mSKeyCommand;
	mCommandMap["move_left"] = mAKeyCommand;
	mCommandMap["move_right"] = mDKeyCommand;

	// Initialize default key bindings
	ReadControlsConfig("Config/settings.toml");

}

void GameInputManager::BindKey(int key, const std::string& commandName)
{
	mKeyBindingMap[key] = commandName;

}

void GameInputManager::RebindKey(int oldKey, int newKey)
{
	if (mKeyBindingMap.find(oldKey) != mKeyBindingMap.end()) {
		std::string commandName = mKeyBindingMap[oldKey];
		mKeyBindingMap.erase(oldKey);
		mKeyBindingMap[newKey] = commandName;
	}
}

void GameInputManager::HandleInput(int key)
{
	if (mKeyBindingMap.find(key) != mKeyBindingMap.end()) {
		std::string commandName = mKeyBindingMap[key];
		if (mCommandMap.find(commandName) != mCommandMap.end()) {
			mCommandMap[commandName]->execute();
		}
	}
}

void GameInputManager::ReadControlsConfig(const std::string& filename)
{
	toml::table config;
	try {

		config = toml::parse_file(filename);

	}
	catch (const toml::parse_error& err)
	{
		std::cerr
			<< "Error parsing file '" << err.source().path
			<< "':\n" << err.description()
			<< "\n (" << err.source().begin << ")\n";
		return;
	}

	auto KeyCodeMap = LoadKeyCodeMap("Config/KeyCodeMap.csv");

	auto controls = config["settings"]["controls"];
	std::string forward = *controls["move_forward"].value<std::string>();
	std::string backward = *controls["move_back"].value<std::string>();


	for (const auto& kvp : *controls.as_table()) {
		const auto& key = kvp.first;
		const auto& value = kvp.second;

		if (value.is_string()) {

			// std::string commandName = key.str();
			std::string commandName = std::string(key.str());

			std::string keyStr = *value.value<std::string>();

			// Look up the key code in the map
			auto it = KeyCodeMap.find(keyStr);
			if (it != KeyCodeMap.end()) {
				int keyCode = it->second;
				BindKey(keyCode, commandName);
			}
			else if (it == KeyCodeMap.end())
			{
				BindKey(keyStr[0], commandName);
			}
			else {
				std::cerr << "Unknown key: " << keyStr << "\n";
			}
		}
	}
}

std::unordered_map<std::string, int> GameInputManager::LoadKeyCodeMap(const std::string& filename)
{
	std::unordered_map<std::string, int> keyCodeMap;
	std::ifstream file(filename);

	if (!file) {
		std::cerr << "Failed to open key code map file: " << filename << std::endl;
		return keyCodeMap;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::istringstream lineStream(line);
		std::string key;
		int code;
		if (std::getline(lineStream, key, ',') && (lineStream >> code)) {
			keyCodeMap[key] = code;
		}
		else {
			std::cerr << "Invalid format in key code map file: " << line << std::endl;
		}
	}

	return keyCodeMap;
}

GameInputManager::~GameInputManager()
{
	delete mWKeyCommand;
	delete mAKeyCommand;
	delete mSKeyCommand;
	delete mDKeyCommand;
}
