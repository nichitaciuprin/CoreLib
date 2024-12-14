#include "BaseLang.hpp"
#include "World.h"

World::World()
{
    subgen = SubgenCreate(1);

    timer1 = 0;

    camera.position = { 0, 1.70f, 3 };
    camera.yaw = 0;
    camera.pitch = 0;

    worldPhysics = make_unique<WorldPhysics>();

    Bound bound;
    bound.p0 = { -3, -1,  0 };
    bound.p1 = {  3,  0, 20 };
    ground = make_unique<StaticBound>(*worldPhysics, bound);

    // enemy 1
    // Vector3 position = { 0, 0, 10 };
    // auto enemy = make_unique<Enemy>(*worldPhysics, position);
    // enemies.push_back(move(enemy));

    // SpawnEnemy();
    // SpawnEnemy();
    // SpawnEnemy();
    // SpawnEnemy();

    for (size_t i = 0; i < 50; i++)
    {
        auto x = SubgenRange(&subgen, -3, 3);
        auto z = SubgenRange(&subgen, 2, 6);
        Vector3 position = { x, 1, z };
        auto projectile = make_shared<Projectile>(*worldPhysics, position);
        projectiles.push_back(move(projectile));
    }
}

void World::Update(float deltaTime)
{
    if (particlesGroup != nullptr)
    {
        auto direction = CameraGetAxisZ(&camera);
        Vector3 rotation = { camera.pitch, -camera.yaw, 0 };
        Vector3 target = camera.position + direction * 2;
        particlesGroup->Update(deltaTime, target, rotation);

        for (auto magnet : particlesGroup->magnets)
            UpdateMagnet(magnet, deltaTime);
    }

    for (auto magnet : magnets)
        UpdateMagnet(magnet, deltaTime);

    if (magnetSingle != nullptr)
    {
        UpdateMagnet(magnetSingle, deltaTime);

        Vector3 result = { 0.75f, 0, 2 };
        result = Vector3RotateX(result, camera.pitch);
        result = Vector3RotateY(result, -camera.yaw);
        result = result + camera.position;
        magnetSingle->position = result;
    }

    // if (timer1 < 0)
    // {
    //     timer1 = SubgenRange(&subgen, 1, 5);
    //     SpawnEnemy();
    // }
    // else
    // {
    //     timer1 -= deltaTime;
    // }

    UpdatePlayer(deltaTime);
    UpdateEnemies(deltaTime);

    worldPhysics->Update(deltaTime);
}

void World::FreezeAll()
{
    for (auto& enemy : enemies)
        enemy->Freeze();
}
void World::ToogleGathering()
{
    gather = !gather;

    if (gather)
    {
        auto direction = CameraGetAxisZ(&camera);
        Vector3 target = camera.position + direction * 2;
        particlesGroup = new ParticlesGroup(target, &subgen);
    }
    else
    {
        delete particlesGroup;
        particlesGroup = nullptr;
    }
}
void World::SpawnEnemy()
{
    Vector3 position;

    position.x = SubgenRange(&subgen, -3, 3);
    position.y = 0;
    position.z = 17;

    auto enemy = make_unique<Enemy>(*worldPhysics, position);
    // auto enemy = make_unique<Enemy>(position);

    enemies.push_back(move(enemy));
}
void World::SetPlayerDirection(Vector2 playerDirection)
{
    this->playerDirection = playerDirection;
}
void World::SetPlayerRotation(Vector2 playerRotation)
{
    this->playerRotation = playerRotation;
}
void World::SpawnProjectile()
{
    auto direction = CameraGetAxisZ(&camera);
    auto position = camera.position + direction / 2;
    auto projectile = make_unique<Projectile>(*worldPhysics, position);
    projectile->SetVelocity(direction * 10);
    projectiles.push_back(move(projectile));
}
void World::PushEnemies()
{
    for (auto& enemy : enemies)
    {
        auto source = camera.position;
        source.y = 0.50f;
        auto target = enemy->GetShape().position;
        auto length = Vector3Distance(source, target);
        if (length > 4) continue;
        enemy->Freeze();
        enemy->ApplyExplosion(source);
    }
}
void World::CreateMagnet()
{
    auto direction = CameraGetAxisZ(&camera);
    auto position = camera.position + direction * 2;
    auto magnet = make_shared<Magnet>(position, &subgen);
    magnets.push_back(magnet);
}
void World::DestroyMagnet()
{
    // if (magnets.size() == 0) return;
    // magnets.pop_back();
    magnets.clear();
}
void World::HandleOneProjectile()
{
    if (magnetSingle == nullptr)
    {
        Vector3 result = { 0.75f, 0, 2.00f };
        auto pitch = MathToRadians(camera.pitch);
        auto yaw = MathToRadians(camera.yaw);
        result = Vector3RotateX(result, pitch);
        result = Vector3RotateY(result, -yaw);
        result = result + camera.position;

        // direction.y = camera.position.y;
        // auto direction = Vec
        magnetSingle = make_shared<Magnet>(result, &subgen);

        // magnetSingle->acc
    }
    else
    {
        auto direction = CameraGetAxisZ(&camera);
        if (auto projectileLock = magnetSingle->projectile.lock())
            projectileLock->SetVelocity(direction * 20);

        magnetSingle = nullptr;
    }
}

void World::UpdatePlayer(float deltaTime)
{
    CameraUpdateFps(&camera, playerDirection * deltaTime * 5, playerRotation);

    camera.position.x = MathClampFloat(camera.position.x, -3.0f,  3.0f);
    camera.position.z = MathClampFloat(camera.position.z, -3.0f, 30.0f);

    playerDirection = {};
    playerRotation = {};
}
void World::UpdateEnemies(float deltaTime)
{
    for (int i = enemies.size() - 1; i >= 0; i--)
    {
        Enemy* enemy = enemies[i].get();

        auto position = enemy->GetFootPosition();

        if (position.y < -10)
        {
            erase_back(enemies, i);

            for (int i = projectiles.size() - 1; i >= 0; i--)
            {
                Projectile* projectile = projectiles[i].get();

                if (projectile->GetParent() == enemy)
                {
                    erase_back(projectiles, i);
                }
            }
        }
    }

    for (auto& enemy : enemies)
    {
        auto playerPosition = camera.position;
        playerPosition.y = 0;
        enemy->Update(playerPosition, deltaTime);
    }

    for (auto& projectile : projectiles)
        projectile->Update(deltaTime);
}

shared_ptr<Projectile> World::TryGetFreeProjectile()
{
    if (projectiles.size() == 0) return nullptr;

    for (size_t i = 0; i < projectiles.size(); i++)
    {
        auto projectile = projectiles[i];

        if (projectile->magnet.expired())
        {
            return projectile;
        }
    }

    return nullptr;
}
shared_ptr<Projectile> World::TryGetFreeClosestProjectile(Vector3 target)
{
    if (projectiles.size() == 0) return nullptr;

    // TODO
    bool found = false;
    float minDist = 99999999.0f;
    size_t minIndex = 0;

    for (size_t i = 0; i < projectiles.size(); i++)
    {
        auto projectile = projectiles[i];

        if (!projectile->magnet.expired()) continue;

        float dist = Vector3Distance(target, projectiles[i]->GetPosition());

        if (minDist > dist)
        {
            minDist = dist;
            minIndex = i;
            found = true;
        }
    }

    if (found)
        return projectiles[minIndex];
    else
        return nullptr;
}

void World::UpdateMagnet(shared_ptr<Magnet> magnet, float deltaTime)
{
    if (magnet->projectile.expired())
    {
        auto projectile = TryGetFreeClosestProjectile(magnet->GetPosition());
        if (projectile == nullptr) return;
        magnet->projectile = projectile;
        projectile->magnet = magnet;
        magnet->removeIfFar = false;
    }

    magnet->OffsetPosition(deltaTime);

    auto projectile = magnet->projectile.lock();

    auto dist = Vector3Distance(magnet->position, projectile->GetPosition());

    if (magnet->removeIfFar)
    {
        if (dist > 2.0f)
        {
            projectile->magnet.reset();
            magnet->projectile.reset();
            return;
        }
    }
    else
    {
        if (dist < 1.0f)
        {
            magnet->removeIfFar = true;
        }
    }

    auto source = projectile->GetPosition();
    auto target = magnet->position + magnet->positionOffsetCurent;

    auto newPosition = Vector3MoveTowards5(source, target, &magnet->projectileVelocity, 10, deltaTime);

    projectile->SetPosition(newPosition);
    projectile->SetVelocity(Vector3Zero());
}
