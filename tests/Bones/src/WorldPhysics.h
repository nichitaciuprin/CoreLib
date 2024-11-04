class EventListener : public rp3d::EventListener
{
    void onContact(const rp3d::CollisionCallback::CallbackData& callbackData) override;
    void onContact(Enemy* enemy, Projectile* projectile);
};

class WorldPhysics
{
public:
    WorldPhysics();
    ~WorldPhysics();

    void Update(float deltaTime);

private:
    static rp3d::PhysicsCommon physicsCommon;
    rp3d::PhysicsWorld* physicsWorld;
    EventListener listener;

    friend class RigidBody;
    friend class RigidBodyK;
    friend class StaticBound;
    friend class World;
};
