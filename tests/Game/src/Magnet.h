#ifndef MAGNET_H
#define MAGNET_H

#include "Helper.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <memory.h>
#include <time.h>
#include <math.h>

#include <iostream>
#include <algorithm>
#include <string>
#include <memory>
#include <vector>
#include <array>
#include <set>
#include <unordered_set>
#include <forward_list>

using namespace std;

class Projectile;

#include "Projectile.h"

class Magnet
{
public:
    Subgen* subgen;
    weak_ptr<Projectile> projectile;

    Vector3 position;
    Vector3 positionOffsetCurent;
    Vector3 positionOffsetTarget;
    Vector3 offsetVelocity;
    Vector3 projectileVelocity;

    float offsetDist;
    float acc;
    float maxSpeed;
    float close;

    bool removeIfFar;

    Magnet(Vector3 position, Subgen* subgen);

    Vector3 GetPosition();
    Vector3 GetPositionOffset();
    Vector3 GetPositionOffsetTarget();
    float GetOffsetDist();

    void OffsetPosition(float deltaTime);
};

#endif
