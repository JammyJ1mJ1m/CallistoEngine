#pragma once
#include "Managers\InputManager.h"
//#include <map>
//#include <memory>
#include <unordered_map>
//#include <string>

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
    //void AddCommand(const std::string& commandName, Command* command);
    void ReadControlsConfig(const std::string& filename);
    std::unordered_map<std::string, int> LoadKeyCodeMap(const std::string& filename);

    GameInputManager();

    // TODO make sure that the commands get deleted in the deconstructor
    ~GameInputManager();
};