#include "WorldWindow.h"

#include "RaylibWrapExt.h"
#include "SysHelper.h"

WorldWindow::WorldWindow(World& world) : world(world)
{
    CreateWindow(500, 500, "Game");
}

bool WorldWindow::ShouldQuit()
{
    return Ray_WindowShouldClose();
}

void WorldWindow::Render()
{
    auto cpuUsage = GetCpuUsage();

    BeginDrawing(cpuUsage);
    {
        StartMode3d(world.camera);
        {
            DrawBound(world.ground->bound, RAY_WHITE);

            for (const auto& enemy : world.enemies)
            {
                auto box = enemy->GetShape();

                if (enemy->Frozen())
                    DrawBoxBlue(box);
                else
                    DrawBoxGreen(box);
            }

            // if (world.particlesGroup != nullptr)
            // {
            //     auto magnets = world.particlesGroup->magnets;
            //     for (auto &&magnet : magnets)
            //     {
            //         Ray_DrawSphere(magnet->GetPosition(), 0.1f, PINK);
            //     }
            // }

            // for (const auto& item : world.magnets)
            // {
            //     auto radius = item->GetOffsetDist() / 2;
            //     Ray_DrawSphere(item->GetPosition(), radius, DARKBLUE);
            //     Ray_DrawSphere(item->GetPositionOffsetTarget(), radius, BLUE);
            //     Ray_DrawSphere(item->GetPositionOffset(), radius, SKYBLUE);
            // }

            for (const auto& item : world.projectiles)
            {
                if (item->magnet.expired())
                    DrawSphere(item->GetPosition(), 0.1f, RAY_RED);
                else
                    DrawSphere(item->GetPosition(), 0.1f, RAY_ORANGE);
            }
        }
        EndMode3D();
    }
    Ray_EndDrawing();
}
void WorldWindow::HandleInput()
{
    auto wasdInput = GetWasdInput();
    auto mouseInput = GetMouseInput();

    world.SetPlayerDirection(wasdInput);
    world.SetPlayerRotation(mouseInput);

    if (Ray_IsKeyPressed(RAY_KEY_Z))
        world.SetPlayerRotation({ MY_PI, 0 });

    if (Ray_IsKeyPressed(RAY_KEY_ONE))
        world.HandleOneProjectile();
        // world.PushEnemies();

    if (Ray_IsKeyPressed(RAY_KEY_TWO))
        world.CreateMagnet();
        // world.SpawnProjectile();

    if (Ray_IsKeyPressed(RAY_KEY_THREE))
        world.DestroyMagnet();
        // world.FreezeAll();

    if (Ray_IsKeyPressed(RAY_KEY_FOUR))
        world.ToogleGathering();

    // if (Ray_IsKeyPressed(RAY_KEY_FIVE))
        // world.DestroyMagnet();
}
