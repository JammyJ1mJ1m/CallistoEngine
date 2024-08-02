#pragma once
#include "Managers\InputManager.h"
class GameInputManager :
    public InputManager
{
private:

public:
    Command* mWalkForwardCommand;
    
    GameInputManager();
    ~GameInputManager();

};

