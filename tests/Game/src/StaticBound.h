#ifndef STATICBOUND_H
#define STATICBOUND_H

class WorldPhysics;

#include "WorldPhysics.h"

class StaticBound
{
public:
    Bound bound;
    StaticBound(WorldPhysics& worldPhysics, Bound bound);
    ~StaticBound();

private:
    WorldPhysics& worldPhysics;
    rp3d::RigidBody* rigidBody;
};

#endif
