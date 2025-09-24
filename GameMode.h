// GameMode.h
#ifndef GAMEMODE_H
#define GAMEMODE_H

// Abstract base class: defines a common interface for different game modes
class GameMode {
public:
// Pure virtual function: must be implemented by any derived class
    virtual void startGame() = 0;  
    // Virtual destructor: ensures safe deletion of derived objects through base pointer
    virtual ~GameMode() {}        
};

#endif
