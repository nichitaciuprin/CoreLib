class StaticBound
{
public:
    Bound bound;
    StaticBound(WorldPhysics& worldPhysics, Bound bound);
    ~StaticBound();

private:
    WorldPhysics& worldPhysics;
    rp3d::RigidBody* rigidBody;
};
