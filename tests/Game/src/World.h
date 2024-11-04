#ifndef WORLD_H
#define WORLD_H

class Projectile;
class WorldPhysics;
class ParticlesGroup;
class StaticBound;

#include "Projectile.h"
#include "WorldPhysics.h"
#include "ParticlesGroup.h"
#include "StaticBound.h"

class World
{
    // TODO maybe create getters/setters instead
    friend class WorldWindow;

public:
    World();

    void Update(float deltaTime);

    void FreezeAll();
    void ToogleGathering();
    void SpawnEnemy();
    void SetPlayerDirection(Vector2 playerDirection);
    void SetPlayerRotation(Vector2 playerRotation);
    void SpawnProjectile();
    void PushEnemies();
    void CreateMagnet();
    void DestroyMagnet();
    void HandleOneProjectile();

private:
    float timer1;
    bool gather = false;
    Subgen subgen;
    Camera camera;
    unique_ptr<WorldPhysics> worldPhysics;
    vector<unique_ptr<Enemy>> enemies;
    unique_ptr<StaticBound> ground;
    shared_ptr<Magnet> magnetSingle;
    vector<shared_ptr<Magnet>> magnets;
    vector<shared_ptr<Projectile>> projectiles;
    Vector2 playerDirection = {};
    Vector2 playerRotation = {};
    ParticlesGroup* particlesGroup = nullptr;

    void UpdatePlayer(float deltaTime);
    void UpdateEnemies(float deltaTime);

    shared_ptr<Projectile> TryGetFreeProjectile();
    shared_ptr<Projectile> TryGetFreeClosestProjectile(Vector3 target);

    void UpdateMagnet(shared_ptr<Magnet> magnet, float deltaTime);
};

#endif
