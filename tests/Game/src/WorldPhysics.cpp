#include "WorldPhysics.h"

void EventListener::onContact(const rp3d::CollisionCallback::CallbackData& callbackData)
{
    for (size_t i = 0; i < callbackData.getNbContactPairs(); i++)
    {
        auto pair = callbackData.getContactPair(i);

        auto userData1 = pair.getBody1()->getUserData(); if (userData1 == nullptr) continue;
        auto userData2 = pair.getBody2()->getUserData(); if (userData2 == nullptr) continue;

        auto rb1 = (RigidBody*)userData1;
        auto rb2 = (RigidBody*)userData2;

        uint8_t rb1Code;
        uint8_t rb2Code;

        void* rb1Ptr;
        void* rb2Ptr;

        rb1->GetUserData(&rb1Code, &rb1Ptr);
        rb2->GetUserData(&rb2Code, &rb2Ptr);

        uint16_t pattern = 0;
        pattern += rb1Code;
        pattern = pattern << 8;
        pattern += rb2Code;

        // TODO
        // 00 RigidBody
        // 01 Enemy
        // 02 Projectile

        switch (pattern)
        {
            case 0x0102: onContact((Enemy*)rb1Ptr, (Projectile*)rb2Ptr); break;
            case 0x0201: onContact((Enemy*)rb2Ptr, (Projectile*)rb1Ptr); break;
            default: break;
        }
    }
}
void EventListener::onContact(Enemy* enemy, Projectile* projectile)
{
    // auto linearVelocity = rb->rigidBody->getLinearVelocity();
    // auto linearVelocity2 = Vector3 { linearVelocity.x, linearVelocity.y, linearVelocity.z };
    // auto impact = Vector3Length(linearVelocity2);

    // if (impact > 10)
    //     enemy.Freeze();

    projectile->SetParent(enemy);
}

WorldPhysics::WorldPhysics()
{
    physicsWorld = physicsCommon.createPhysicsWorld();

    physicsWorld->setEventListener(&listener);
}
WorldPhysics::~WorldPhysics()
{
    physicsCommon.destroyPhysicsWorld(physicsWorld);
}
void WorldPhysics::Update(float deltaTime)
{
    physicsWorld->update(deltaTime);
}
rp3d::PhysicsCommon WorldPhysics::physicsCommon;
