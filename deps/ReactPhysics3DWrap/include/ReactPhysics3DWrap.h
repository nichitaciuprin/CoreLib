#ifndef REACTPHYSICS3DWRAP_H
#define REACTPHYSICS3DWRAP_H

#include <Helper.h>
#include <reactphysics3d/reactphysics3d.h>

namespace rp3d = reactphysics3d;

inline Vector3 ToEuler(rp3d::Quaternion rot)
{
    auto quat = Vector4 { rot.x, rot.y, rot.z, rot.w };
    auto euler = ToEuler(quat);
    return Vector3 { -euler.x, -euler.y, -euler.z };
}
inline rp3d::Quaternion FromEuler(Vector3 euler)
{
    euler.x = -euler.x;
    euler.y = -euler.y;
    euler.z = -euler.z;

    auto quat = ToQuaternion(euler);
    auto quat2 = rp3d::Quaternion { quat.x, quat.y, quat.z, quat.w };

    return quat2;

    // auto quat = rp3d::Quaternion::fromEulerAngles(-euler.x, -euler.y, -euler.z);
    // return rp3d::Quaternion { quat.x, quat.y, quat.z, quat.w };
}

inline Vector3 Rp3dGetPosition(const rp3d::RigidBody& rb)
{
    auto transform = rb.getTransform();
    auto position = transform.getPosition();
    return { position.x, position.y, position.z };
}
inline Vector3 Rp3dGetRotation(const rp3d::RigidBody& rb)
{
    auto transform = rb.getTransform();
    auto quaternion = transform.getOrientation();
    auto rotation = ToEuler(quaternion);
    return rotation;
}
inline Pose Rp3dGetPose(const rp3d::RigidBody& rb)
{
    Pose pose;
    pose.position = Rp3dGetPosition(rb);
    pose.rotation = Rp3dGetRotation(rb);
    return pose;
}
inline void Rp3dSetPose(rp3d::RigidBody& rb, Pose pose)
{
    rp3d::Transform transform;
    rp3d::Vector3 position = { pose.position.x, pose.position.y, pose.position.z };
    rp3d::Quaternion rotation = FromEuler(pose.rotation);
    transform.setPosition(position);
    transform.setOrientation(rotation);
    rb.setTransform(transform);
}

#endif
