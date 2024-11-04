#ifndef ARROW_H
#define ARROW_H

class Enemy;
class Projectile;
class WorldPhysics;

#include "Enemy.h"
#include "Projectile.h"
#include "WorldPhysics.h"

class Arrow
{
public:
    Arrow(WorldPhysics& worldPhysics, Vector3 position);
    void SetVelocity(Vector3 velocity);
    Vector3 GetPosition() const;
    void Update(float deltaTime);
    void SetParent(Enemy* parent);
    Enemy* GetParent() const;

private:
    Enemy* parent;
    Pose localPosition;
    unique_ptr<RigidBody> rigidBody;
    WorldPhysics& worldPhysics;
};

#endif
