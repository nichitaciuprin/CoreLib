#include "Magnet.h"

Magnet::Magnet(Vector3 position, Subgen* subgen)
{
    this->position = position;
    this->subgen = subgen;

    this->positionOffsetCurent = Vector3Zero();
    this->positionOffsetTarget = Vector3Zero();
    this->offsetVelocity = Vector3Zero();
    this->projectileVelocity = Vector3Zero();

    // close      = 0.01f;
    // offsetDist = 0.20f;
    // maxSpeed   = offsetDist * 2;
    // acc        = maxSpeed * 2;

    close      = 0.01f;
    offsetDist = 0.02f;
    maxSpeed   = offsetDist * 2;
    acc        = maxSpeed * 2;

    removeIfFar = false;
}

Vector3 Magnet::GetPosition()
{
    return position;
}
Vector3 Magnet::GetPositionOffset()
{
    return position + positionOffsetCurent;
}
Vector3 Magnet::GetPositionOffsetTarget()
{
    return position + positionOffsetTarget;
}
float Magnet::GetOffsetDist()
{
    return offsetDist;
}

void Magnet::OffsetPosition(float deltaTime)
{
    auto isClose = Vector3Distance(positionOffsetCurent, positionOffsetTarget) <= close;
    if (isClose)
    {
        auto x = SubgenRange(subgen, -1, 1);
        auto y = SubgenRange(subgen, -1, 1);
        auto z = SubgenRange(subgen, -1, 1);

        Vector3 vecNorm = Vector3Normalize({ x, y, z });

        positionOffsetTarget = vecNorm * offsetDist;
    }

    // positionOffsetCurent = Vector3MoveTowards4(positionOffsetCurent, positionOffsetTarget, &offsetVelocity, acc, deltaTime);
    positionOffsetCurent = Vector3MoveTowards3(positionOffsetCurent, positionOffsetTarget, &offsetVelocity, acc, maxSpeed, deltaTime);
}
