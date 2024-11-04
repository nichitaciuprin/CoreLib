#include "Enemy.h"

Enemy::Enemy(WorldPhysics& worldPhysics, Vector3 position) : worldPhysics(worldPhysics)
{
    Vector3 rotation = {};
    this->rigidBody = make_unique<RigidBody>(worldPhysics, position, rotation, GetHalfs());
    this->rigidBody->SetUserData(1, this);
    this->frozen = false;
}
void Enemy::Update(Vector3 playerPosition, float deltaTime)
{
    if (frozen)
    {
        if (rigidBody->IsSleeping())
            Unfreeze();
    }
    else
    {
        // TODO

        // auto footPosition = GetFootPosition();

        // auto source = Vector2 { footPosition.x, footPosition.z };
        // auto target = Vector2 { playerPosition.x, playerPosition.z };

        // auto dir = Vector2Normalize(target - source);

        // auto result = Vector2MoveTowards(source, target, 3 * deltaTime, 1);
        // auto position = Vector3 { result.x, 0, result.y };

        // Vector3 rotation = {};
        // rotation.y = -Vector2Rotation(dir);

        // SetFootPosition(position, rotation);
    }
}
void Enemy::Freeze()
{
    rigidBody->SetDynamic();
    frozen = true;
}
void Enemy::Unfreeze()
{
    rigidBody->SetKinematic();
    frozen = false;

    Vector3 rotation = {};
    Vector3 position = GetFootPosition();
    position.y = 0;

    SetFootPosition(position, rotation);
}
void Enemy::ApplyExplosion(Vector3 source)
{
    if (!frozen) return;

    float power = 7;

    auto pos1 = source;
    auto pos3 = rigidBody->GetPosition();
    auto diff = pos3 - pos1;

    auto dir = Vector3Normalize(diff);

    auto force1 = dir * power;
    auto force2 = Vector3 { force1.x, force1.y, force1.z };

    rigidBody->SetLinearVelocity(force2);
}
void Enemy::SetFootPosition(Vector3 position, Vector3 rotation)
{
    // auto shape = GetShape();

    auto offset = Vector3 { 0, 1.75f / 2, 0 };

    // offset = Vector3RotateX(offset, shape.rotation.x);
    // offset = Vector3RotateY(offset, shape.rotation.y);
    // offset = Vector3RotateZ(offset, shape.rotation.z);

    position += offset;

    Pose pose = { position, rotation };

    rigidBody->SetPose(pose);
}
bool Enemy::Frozen() const
{
    return frozen;
}
Box Enemy::GetShape() const
{
    auto pose = rigidBody->GetPose();

    Box box;
    box.position = pose.position;
    box.rotation = pose.rotation;
    box.halfExtent = GetHalfs();

    return box;
}
Pose Enemy::GetPose() const
{
    return rigidBody->GetPose();
}
Vector3 Enemy::GetHalfs() const
{
    return
    {
        0.60f / 2,
        1.75f / 2,
        0.30f / 2
    };
}
Vector3 Enemy::GetFootPosition() const
{
    auto shape = GetShape();

    auto offset = Vector3 { 0, -(1.75f / 2), 0 };

    offset = Vector3RotateX(offset, shape.rotation.x);
    offset = Vector3RotateY(offset, shape.rotation.y);
    offset = Vector3RotateZ(offset, shape.rotation.z);

    return shape.position + offset;
}
