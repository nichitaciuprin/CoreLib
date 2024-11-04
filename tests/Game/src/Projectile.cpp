#include "Projectile.h"

Projectile::Projectile(WorldPhysics& worldPhysics, Vector3 position) : worldPhysics(worldPhysics)
{
    rigidBody = make_unique<RigidBody>(worldPhysics, position);
    rigidBody->SetUserData(2, this);
    parent = nullptr;
}
// Projectile::~Projectile()
// {
//     if (auto magnetLock = magnet.lock())
//     {
//         magnetLock->projectile.reset
//     }
// }
void Projectile::SetDynamic()
{
    rigidBody->SetDynamic();
}
void Projectile::SetKinematic()
{
    rigidBody->SetKinematic();
}
void Projectile::SetPosition(Vector3 position)
{
    rigidBody->SetPosition(position);
}
void Projectile::SetVelocity(Vector3 velocity)
{
    rigidBody->SetLinearVelocity(velocity);
}
void Projectile::SetVelocity2(Vector3 velocity)
{
    rigidBody->SetForce(velocity);
}
Vector3 Projectile::GetPosition() const
{
    return rigidBody->GetPosition();
}
void Projectile::Update(float deltaTime)
{
    if (parent == nullptr) return;

    auto pose1 = parent->GetPose();
    auto pose2 = localPosition;
    auto pose3 = GetWorldPose(pose1, pose2);
    this->rigidBody->SetPose(pose3);
}
void Projectile::SetParent(Enemy* parent)
{
    auto child = this;

    child->rigidBody->SetIsActive(false);

    auto pose1 = parent->GetPose();
    auto pose2 = child->rigidBody->GetPose();

    this->parent = parent;
    this->localPosition = GetLocalPose(pose1, pose2);
}
Enemy* Projectile::GetParent() const
{
    return this->parent;
}
