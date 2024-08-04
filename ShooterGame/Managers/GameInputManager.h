#pragma once
#include "Managers\InputManager.h"
#include <map>
//#include <memory>
#include <string>

using CommandMap = std::map<std::string, Command*>;
using CommandMapIterator = CommandMap::iterator;


using KeyBindingMap = std::map<int, std::string>;
using KeyBindingMapIterator = KeyBindingMap::iterator;


class GameInputManager : public InputManager
{
private:
    Command* mWKeyCommand;
    Command* mAKeyCommand;
    Command* mSKeyCommand;
    Command* mDKeyCommand;

    // map of keys to commands
    CommandMap mCommandMap;
    
    // map of commands to names
    KeyBindingMap mKeyBindingMap; // Map of key to command name

public:
    void BindKey(int key, const std::string& commandName);
    void RebindKey(int oldKey, int newKey);
    void HandleInput(int key);

    GameInputManager();

    // TODO make sure that the commands get deleted in the deconstructor
    ~GameInputManager();
};