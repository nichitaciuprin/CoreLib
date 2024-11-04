#ifndef WORLDWINDOW_H
#define WORLDWINDOW_H

#include "World.h"

class WorldWindow
{
public:
    WorldWindow(World& world);

    bool ShouldQuit();

    void Render();
    void HandleInput();

private:
    World& world;
};

#endif
