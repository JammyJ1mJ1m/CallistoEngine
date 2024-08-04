#include "GameInputManager.h"
#include "../GameCommands/GameCommands.h"

GameInputManager::GameInputManager()
{
    mWKeyCommand = new MoveForwardCommand();
mSKeyCommand = new MoveBackCommand();
 mAKeyCommand = new MoveLeftCommand();
 mDKeyCommand = new MoveRightCommand();

    // Initialize default commands
    mCommandMap["MoveForward"] = mWKeyCommand;
    mCommandMap["MoveDown"] = mSKeyCommand;
    mCommandMap["MoveLeft"] = mAKeyCommand;
    mCommandMap["MoveRight"] = mDKeyCommand;

     // Initialize default key bindings
    BindKey('W', "MoveForward");
    BindKey('S', "MoveDown");
    BindKey('A', "MoveLeft");
    BindKey('D', "MoveRight");
    // Similarly, bind 'A' and 'D'

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



GameInputManager::~GameInputManager()
{
		delete mWKeyCommand;
		// delete mAKeyCommand;
		// delete mSKeyCommand;
		// delete mDKeyCommand;
}
