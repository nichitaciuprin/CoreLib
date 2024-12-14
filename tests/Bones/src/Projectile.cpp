Projectile::Projectile(WorldPhysics& worldPhysics, Vector3 position) : worldPhysics(worldPhysics)
{
    rigidBody = make_unique<RigidBody>(worldPhysics, position);
    rigidBody->SetUserData(2, this);
    parent = nullptr;
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
    auto pose3 = PoseGetWorld(pose1, pose2);
    this->rigidBody->SetPose(pose3);
}
void Projectile::SetParent(Enemy* parent)
{
    auto child = this;

    child->rigidBody->SetIsActive(false);

    auto pose1 = parent->GetPose();
    auto pose2 = child->rigidBody->GetPose();

    this->parent = parent;
    this->localPosition = PoseGetLocal(pose1, pose2);
}
Enemy* Projectile::GetParent() const
{
    return this->parent;
}
