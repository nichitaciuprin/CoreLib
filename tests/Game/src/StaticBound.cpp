#include "StaticBound.h"
#include "BaseMath.hpp"

StaticBound::StaticBound(WorldPhysics& worldPhysics, Bound bound) : worldPhysics(worldPhysics)
{
    this->bound = bound;

    rp3d::Transform transformZero;

    auto center = BoundCenter(&bound);
    auto halfs = BoundSize(&bound) / 2;

    auto position = rp3d::Vector3(center.x, center.y, center.z);
    auto halfExtents = rp3d::Vector3(halfs.x, halfs.y, halfs.z);
    auto rotation = rp3d::Quaternion::identity();

    auto transform = rp3d::Transform(position, rotation);
    auto shape = worldPhysics.physicsCommon.createBoxShape(halfExtents);

    rigidBody = worldPhysics.physicsWorld->createRigidBody(transform);

    rigidBody->setType(rp3d::BodyType::STATIC);
    rigidBody->addCollider(shape, transformZero);
}
StaticBound::~StaticBound()
{
    worldPhysics.physicsWorld->destroyRigidBody(rigidBody);
}
