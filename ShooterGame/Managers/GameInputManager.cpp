#include "GameInputManager.h"
#include "../GameCommands/GameCommands.h"
#include "toml.hpp"
#include <iostream>
#include <sstream>

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

	auto controls = config["settings"]["controls"];
	std::string forward = *controls["move_forward"].value<std::string>();
	std::string backward = *controls["move_back"].value<std::string>();

	// Loop through the controls table
	for (const auto& kvp : *controls.as_table()) {
		const auto& key = kvp.first;
		const auto& value = kvp.second;

		if (value.is_string()) {
			std::string keyStr = std::string( key.str());
			auto keyCode = *value.value<std::string>();
			BindKey(keyCode[0], keyStr);
		}
	}
}

GameInputManager::~GameInputManager()
{
	delete mWKeyCommand;
	delete mAKeyCommand;
	delete mSKeyCommand;
	delete mDKeyCommand;
}
