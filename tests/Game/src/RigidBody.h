#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "BaseMath.h"


class WorldPhysics;

#include "WorldPhysics.h"

class RigidBody
{
public:
    RigidBody(WorldPhysics& worldPhysics, Vector3 position);
    RigidBody(WorldPhysics& worldPhysics, Vector3 position, Vector3 rotation, Vector3 halfs);
    ~RigidBody();

    Pose GetPose() const;
    Vector3 GetPosition() const;
    Vector3 GetRotation() const;
    bool IsSleeping() const;
    void SetPose(Pose pose);
    void SetPosition(Vector3 position);
    void SetRotation(Vector3 rotation);
    void SetUserData(uint8_t code, void* ptr);
    void GetUserData(uint8_t* codeOut, void** ptrOut) const;
    void SetForce(Vector3 velocity);
    void SetLinearVelocity(Vector3 velocity);
    void SetDynamic();
    void SetKinematic();
    void SetIsActive(bool isActive);
    void SetGravity(bool isEnable);

private:
    rp3d::RigidBody* rigidBody;
    rp3d::Transform transform2;
    WorldPhysics& worldPhysics;
    uint8_t userDataCode;
    void* userDataPtr;
};

#endif
