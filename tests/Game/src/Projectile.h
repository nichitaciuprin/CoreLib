#ifndef PROJECTILE_H
#define PROJECTILE_H

class Magnet;
class WorldPhysics;
class Enemy;

#include "Magnet.h"
#include "WorldPhysics.h"
#include "Enemy.h"

class Projectile
{
public:
    Projectile(WorldPhysics& worldPhysics, Vector3 position);
    // ~Projectile();
    void SetDynamic();
    void SetKinematic();
    void SetPosition(Vector3 position);
    void SetVelocity(Vector3 velocity);
    void SetVelocity2(Vector3 velocity);
    Vector3 GetPosition() const;
    void Update(float deltaTime);
    void SetParent(Enemy* parent);
    Enemy* GetParent() const;

    weak_ptr<Magnet> magnet;

private:
    Enemy* parent;
    Pose localPosition;
    unique_ptr<RigidBody> rigidBody;
    WorldPhysics& worldPhysics;
};

#endif
