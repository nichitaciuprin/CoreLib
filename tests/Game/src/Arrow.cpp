#include "Arrow.h"

Arrow::Arrow(WorldPhysics& worldPhysics, Vector3 position) : worldPhysics(worldPhysics)
{
    rigidBody = make_unique<RigidBody>(worldPhysics, position);
    rigidBody->SetUserData(2, this);
    parent = nullptr;
}
void Arrow::SetVelocity(Vector3 velocity)
{
    rigidBody->SetLinearVelocity(velocity);
}
Vector3 Arrow::GetPosition() const
{
    return rigidBody->GetPosition();
}
void Arrow::Update(float deltaTime)
{
    if (parent == nullptr) return;

    auto pose1 = parent->GetPose();
    auto pose2 = localPosition;
    auto pose3 = GetWorldPose(pose1, pose2);
    this->rigidBody->SetPose(pose3);
}
void Arrow::SetParent(Enemy* parent)
{
    auto child = this;

    child->rigidBody->SetIsActive(false);

    auto pose1 = parent->GetPose();
    auto pose2 = child->rigidBody->GetPose();

    this->parent = parent;
    this->localPosition = GetLocalPose(pose1, pose2);
}
Enemy* Arrow::GetParent() const
{
    return this->parent;
}
