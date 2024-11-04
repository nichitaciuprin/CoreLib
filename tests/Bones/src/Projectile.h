class Projectile
{
public:
    Projectile(WorldPhysics& worldPhysics, Vector3 position);
    void SetVelocity(Vector3 velocity);
    void SetVelocity2(Vector3 velocity);
    Vector3 GetPosition() const;
    void Update(float deltaTime);
    void SetParent(Enemy* parent);
    Enemy* GetParent() const;

private:
    Enemy* parent;
    Pose localPosition;
    unique_ptr<RigidBody> rigidBody;
    WorldPhysics& worldPhysics;
};
