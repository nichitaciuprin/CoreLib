#include "ParticlesGroup.h"
#include "HelperExt.h"

ParticlesGroup::ParticlesGroup(Vector3 position, Subgen* subgen)
{
    localPositions[0] = {  0,  0,  0 };
    localPositions[1] = {  0,  2,  0 };
    localPositions[2] = {  0,  1,  0 };
    localPositions[3] = {  0, -1,  0 };
    localPositions[4] = {  0, -2,  0 };
    localPositions[5] = { -2,  0,  0 };
    localPositions[6] = { -1,  0,  0 };
    localPositions[7] = {  1,  0,  0 };
    localPositions[8] = {  2,  0,  0 };

    for (size_t i = 0; i < 9; i++)
        localPositions[i] = localPositions[i] / 4;

    for (size_t i = 0; i < 9; i++)
    {
        auto finalPosition = position + localPositions[i];

        auto item = make_shared<Magnet>(finalPosition, subgen);
        magnets.push_back(item);
    }
}

void ParticlesGroup::Update(float deltaTime, Vector3 position, Vector3 rotation)
{
    for (size_t i = 0; i < 9; i++)
    {
        Vector3 finalPosition = localPositions[i];
        finalPosition = Vector3Rotate(finalPosition, rotation);
        finalPosition = finalPosition + position;
        magnets[i]->position = finalPosition;
    }
}