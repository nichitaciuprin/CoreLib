#ifndef PARTICLESGROUP_H
#define PARTICLESGROUP_H

class Magnet;

#include "Magnet.h"

class ParticlesGroup
{
public:
    Vector3 localPositions[9] = {};
    vector<shared_ptr<Magnet>> magnets;

    ParticlesGroup(Vector3 position, Subgen* subgen);

    void Update(float deltaTime, Vector3 position, Vector3 rotation);
};

#endif
