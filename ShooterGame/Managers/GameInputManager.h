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
    Command* mRotateLeftCommand;
    Command* mRotateRightCommand;

    Command* mAltFwdKeyCommand;
    Command* mAltLeftKeyCommand;
    Command* mAltBckKeyCommand;
    Command* mAltRightKeyCommand;

    // map of keys to commands
    CommandMap mCommandMap;
    
    // map of commands to names
    KeyBindingMap mKeyBindingMap; // Map of key to command name

public:
    void BindKey(int key, const std::string& commandName);
    void RebindKey(int oldKey, int newKey);

    // Original implementation. Works but is kind of limited. 
    // void HandleInput(int key);

    // New implementation. Returns a command object that can be executed by the caller.
     Command* HandleInput(int key);

    //void AddCommand(const std::string& commandName, Command* command);
    void ReadControlsConfig(const std::string& filename);
    std::unordered_map<std::string, int> LoadKeyCodeMap(const std::string& filename);

    GameInputManager();

    // TODO make sure that the commands get deleted in the deconstructor
    ~GameInputManager();
};