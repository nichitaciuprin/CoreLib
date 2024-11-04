class Enemy
{
public:
    Enemy(WorldPhysics& worldPhysics, Vector3 position);
    void Update(Vector3 playerPosition, float deltaTime);
    void Freeze();
    void Unfreeze();
    void ApplyExplosion(Vector3 source);
    bool Frozen() const;
    void SetFootPosition(Vector3 position, Vector3 rotation);
    Box GetShape() const;
    Pose GetPose() const;
    Vector3 GetHalfs() const;
    Vector3 GetFootPosition() const;

private:
    bool frozen;
    WorldPhysics& worldPhysics;
    unique_ptr<RigidBody> rigidBody;
};
