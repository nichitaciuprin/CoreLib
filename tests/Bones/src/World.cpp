ParticlesForm* particlesForm1 = nullptr;

World::World()
{
    subgen = SubgenCreate(1);

    timer1 = 0;

    camera.position = { 0, 1.70f, 3 };
    camera.yaw = 0;
    camera.pitch = 0;

    worldPhysics = make_unique<WorldPhysics>();

    Bound bound;
    bound.p0 = { -3, -1,  0 };
    bound.p1 = {  3,  0, 20 };
    ground = make_unique<StaticBound>(*worldPhysics, bound);

    // enemy 1
    Vector3 position = { 0, 0, 10 };
    auto enemy = make_unique<Enemy>(*worldPhysics, position);
    enemies.push_back(move(enemy));

    // SpawnEnemy();
    // SpawnEnemy();
    // SpawnEnemy();
    // SpawnEnemy();

    for (size_t i = 0; i < 50; i++)
    {
        auto x = SubgenRange(&subgen, -3, 3);
        auto z = SubgenRange(&subgen, 2, 6);
        Vector3 position = { x, 1, z };
        auto projectile = make_unique<Projectile>(*worldPhysics, position);
        projectiles.push_back(move(projectile));
    }
}
void World::Update(Input input, float deltaTime)
{
    if (input.key1)
        PushEnemies();

    if (input.key2)
        SpawnProjectile();

    if (input.key3)
    {
        for (auto& enemy : enemies)
            enemy->Freeze();
    }

    // if (input.key4)
    // {
    //     auto direction = GetAxisZ(&camera);
    //     direction.y = 0;
    //     direction = Vector3Normalize(direction);

    //     auto position = camera.position + direction;

    //     auto projectile = make_unique<Projectile>(*worldPhysics, position);
    //     // projectile->SetVelocity(direction * 10);
    //     projectiles.push_back(move(projectile));
    // }

    if (input.key4)
    {
        gather = !gather;

        if (gather)
        {
            // auto direction = GetAxisZ(&camera);
            // Vector3 target = camera.position + direction * 2;
            particlesForm1 = new ParticlesForm();
        }
        else
        {
            delete particlesForm1;
            particlesForm1 = nullptr;
        }
    }

    if (particlesForm1 != nullptr)
    {
        auto direction = GetAxisZ(&camera);
        Vector3 target = camera.position + direction * 2;
        particlesForm1->Update(deltaTime, &subgen, target, projectiles);
    }

    // if (timer1 < 0)
    // {
    //     timer1 = SubgenRange(&subgen, 1, 5);
    //     SpawnEnemy();
    // }
    // else
    // {
    //     timer1 -= deltaTime;
    // }

    UpdatePlayer(input, deltaTime);
    UpdateEnemies(deltaTime);

    worldPhysics->Update(deltaTime);
}
void World::SpawnEnemy()
{
    Vector3 position;

    position.x = SubgenRange(&subgen, -3, 3);
    position.y = 0;
    position.z = 17;

    auto enemy = make_unique<Enemy>(*worldPhysics, position);
    // auto enemy = make_unique<Enemy>(position);

    enemies.push_back(move(enemy));
}
void World::UpdatePlayer(Input input, float deltaTime)
{
    UpdateCameraFps(camera, input.wasd * deltaTime * 5, input.mouseDelta / 5);
    camera.position.x = MathClamp(camera.position.x, -3.0f,  3.0f);
    camera.position.z = MathClamp(camera.position.z, -3.0f, 30.0f);
}
void World::UpdateEnemies(float deltaTime)
{
    for (int i = enemies.size() - 1; i >= 0; i--)
    {
        Enemy* enemy = enemies[i].get();

        auto position = enemy->GetFootPosition();

        if (position.y < -10)
        {
            erase_back(enemies, i);

            for (int i = projectiles.size() - 1; i >= 0; i--)
            {
                Projectile* projectile = projectiles[i].get();

                if (projectile->GetParent() == enemy)
                {
                    erase_back(projectiles, i);
                }
            }
        }
    }

    for (auto& enemy : enemies)
    {
        auto playerPosition = camera.position;
        playerPosition.y = 0;
        enemy->Update(playerPosition, deltaTime);
    }

    for (auto& projectile : projectiles)
        projectile->Update(deltaTime);
}
void World::SpawnProjectile()
{
    auto direction = GetAxisZ(&camera);
    auto position = camera.position + direction / 2;
    auto projectile = make_unique<Projectile>(*worldPhysics, position);
    projectile->SetVelocity(direction * 10);
    projectiles.push_back(move(projectile));
}
void World::PushEnemies()
{
    for (auto& enemy : enemies)
    {
        auto source = camera.position;
        source.y = 0.50f;
        auto target = enemy->GetShape().position;
        auto length = Vector3Distance(source, target);
        if (length > 4) continue;
        enemy->Freeze();
        enemy->ApplyExplosion(source);
    }
}

// TODO fix this
bool windowCreated = false;
void World::Render()
{
    if (!windowCreated)
    {
        windowCreated = true;
        CreateWindow();
    }

    auto cpuUsage = GetCpuUsage();

    Ray_BeginDraw(cpuUsage);
    {
        Ray_StartMode3d(camera);
        {
            DrawBound(ground->bound, WHITE);

            for (const auto& enemy : enemies)
            {
                auto box = enemy->GetShape();

                if (enemy->Frozen())
                    DrawBoxBlue(box);
                else
                    DrawBoxGreen(box);
            }

            // if (particlesForm1 != nullptr)
            // {
            //     for (size_t i = 0; i < 9; i++)
            //         Ray_DrawSphere(particlesForm1->finalForm[i], 0.1f, PINK);
            // }

            for (const auto& item : projectiles)
            {
                Ray_DrawSphere(item->GetPosition(), 0.1f, RED);
            }
        }
        Ray_FinishMode3d();
    }
    Ray_EndDraw();
}
