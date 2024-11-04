#include "SysHelper.h"
#include "World.h"
#include "WorldWindow.h"

#include "ParticlesGroup.cpp"
#include "Magnet.cpp"
#include "Arrow.cpp"
#include "Projectile.cpp"
#include "WorldPhysics.cpp"
#include "RigidBody.cpp"
#include "StaticBound.cpp"
#include "Enemy.cpp"
#include "World.cpp"
#include "WorldWindow.cpp"

int main()
{
    auto world = make_unique<World>();
    auto worldWindow = make_unique<WorldWindow>(*world);

    long timeStep = 8;
    float deltaTime = timeStep / 1000.0f;

    while (true)
    {
        long endTime = GetTime() + timeStep;

        worldWindow->Render();
        worldWindow->HandleInput();

        world->Update(deltaTime);

        long haltTime = endTime - GetTime();
        if (haltTime > 0)
            Halt(haltTime);

        if (worldWindow->ShouldQuit()) break;
    }

	return 0;
}
