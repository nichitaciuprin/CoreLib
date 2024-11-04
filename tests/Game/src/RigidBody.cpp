#include "RigidBody.h"
#include "ReactPhysics3DWrap.h"

RigidBody::RigidBody(WorldPhysics& worldPhysics, Vector3 position) : worldPhysics(worldPhysics)
{
    rp3d::Transform transformZero;

    auto positionRp = rp3d::Vector3(position.x, position.y, position.z);

    auto rotationRp = rp3d::Quaternion::identity();

    auto transform = rp3d::Transform(positionRp, rotationRp);

    rigidBody = worldPhysics.physicsWorld->createRigidBody(transform);

    rigidBody->setType(rp3d::BodyType::DYNAMIC);
    rigidBody->setMass(1);

    auto shape = worldPhysics.physicsCommon.createSphereShape(0.1f);
    auto collider = rigidBody->addCollider(shape, transformZero);

    auto material = collider->getMaterial();
    material.setBounciness(0.50f);
    material.setFrictionCoefficient(0.50f);
    collider->setMaterial(material);

    rigidBody->setUserData(this);

    userDataCode = 0;
    userDataPtr = nullptr;
}
RigidBody::RigidBody(WorldPhysics& worldPhysics, Vector3 position, Vector3 rotation, Vector3 halfs) : worldPhysics(worldPhysics)
{
    rp3d::Transform transformZero;

    auto positionRp = rp3d::Vector3(position.x, position.y + halfs.y, position.z);
    auto rotationRp = FromEuler(rotation);

    auto transform = rp3d::Transform(positionRp, rotationRp);

    rigidBody = worldPhysics.physicsWorld->createRigidBody(transform);

    rigidBody->setType(rp3d::BodyType::KINEMATIC);
    rigidBody->setMass(7);

    auto shape = worldPhysics.physicsCommon.createBoxShape(rp3d::Vector3(halfs.x, halfs.y, halfs.z));
    auto collider = rigidBody->addCollider(shape, transformZero);

    auto material = collider->getMaterial();
    material.setBounciness(0.10f);
    material.setFrictionCoefficient(0.50f);
    collider->setMaterial(material);

    rigidBody->setUserData(this);

    userDataCode = 0;
    userDataPtr = nullptr;
}
RigidBody::~RigidBody()
{
    worldPhysics.physicsWorld->destroyRigidBody(rigidBody);
}

Pose RigidBody::GetPose() const
{
    return Rp3dGetPose(*rigidBody);
}
Vector3 RigidBody::GetPosition() const
{
    return Rp3dGetPosition(*rigidBody);
}
Vector3 RigidBody::GetRotation() const
{
    return Rp3dGetRotation(*rigidBody);
}
bool RigidBody::IsSleeping() const
{
    return rigidBody->isSleeping();
}
void RigidBody::SetPose(Pose pose)
{
    Rp3dSetPose(*rigidBody, pose);
}
void RigidBody::SetPosition(Vector3 position)
{
    transform2.setPosition(rp3d::Vector3 { position.x, position.y, position.z });
    rigidBody->setTransform(transform2);
}
void RigidBody::SetRotation(Vector3 rotation)
{
    transform2.setOrientation(FromEuler(rotation));
    rigidBody->setTransform(transform2);
}
void RigidBody::SetUserData(uint8_t code, void* ptr)
{
    this->userDataCode = code;
    this->userDataPtr= ptr;
}
void RigidBody::GetUserData(uint8_t* codeOut, void** ptrOut) const
{
    *codeOut = this->userDataCode;
    *ptrOut = this->userDataPtr;
}
void RigidBody::SetForce(Vector3 velocity)
{
    auto velocityRp = rp3d::Vector3(velocity.x, velocity.y, velocity.z);
    rigidBody->applyWorldForceAtCenterOfMass(velocityRp);
}
void RigidBody::SetLinearVelocity(Vector3 velocity)
{
    auto velocityRp = rp3d::Vector3(velocity.x, velocity.y, velocity.z);
    rigidBody->setLinearVelocity(velocityRp);
}
void RigidBody::SetDynamic()
{
    rigidBody->setType(rp3d::BodyType::DYNAMIC);
}
void RigidBody::SetKinematic()
{
    rigidBody->setType(rp3d::BodyType::KINEMATIC);
}
void RigidBody::SetIsActive(bool isActive)
{
    rigidBody->setIsActive(isActive);
}
void RigidBody::SetGravity(bool isEnable)
{
    rigidBody->enableGravity(isEnable);
}
