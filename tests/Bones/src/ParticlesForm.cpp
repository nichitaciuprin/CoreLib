ParticlesForm::ParticlesForm()
{
    localInitForm[0] = {  0,  0,  0 };
    localInitForm[1] = {  0,  2,  0 };
    localInitForm[2] = {  0,  1,  0 };
    localInitForm[3] = {  0, -1,  0 };
    localInitForm[4] = {  0, -2,  0 };
    localInitForm[5] = { -2,  0,  0 };
    localInitForm[6] = { -1,  0,  0 };
    localInitForm[7] = {  1,  0,  0 };
    localInitForm[8] = {  2,  0,  0 };

    for (size_t i = 0; i < 9; i++)
        localCurentForm[i] = localInitForm[i]/4;
}
void ParticlesForm::Update(float deltaTime, Subgen* subgen, Vector3 target, vector<shared_ptr<Projectile>>& projectiles)
{
    size_t count = 9;

    if (timer > 0)
    {
        timer -= deltaTime;
    }
    else
    {
        timer = 0.500f;

        // updates targetForm
        for (size_t i = 0; i < 9; i++)
        {
            // localTargetForm[i] = localInitForm[i];

            auto x = SubgenRange(subgen, -1, 1);
            auto y = SubgenRange(subgen, -1, 1);
            auto z = SubgenRange(subgen, -1, 1);

            auto vec1 = Vector3Normalize({ x, y, z }) * 0.025f;

            localTargetForm[i] = localInitForm[i]/4 + vec1;
        }
    }

    for (size_t i = 0; i < count; i++)
    {
        localCurentForm[i] = Vector3MoveTowards(localCurentForm[i], localTargetForm[i], deltaTime/20);
        finalForm[i] = target + localCurentForm[i];
    }

    for (size_t i = 0; i < count; i++)
    {
        size_t index1 = i;
        float dist1 = Vector3Distance(finalForm[i], projectiles[i]->GetPosition());

        for (size_t j = i+1; j < projectiles.size(); j++)
        {
            size_t index2 = j;
            float dist2 = Vector3Distance(finalForm[i], projectiles[j]->GetPosition());

            if (dist1 > dist2)
            {
                index1 = index2;
                dist1 = dist2;
            }
        }

        if (i != index1)
            swap(projectiles[i], projectiles[index1]);
    }

    for (size_t i = 0; i < count; i++)
    {
        auto finalTarget = finalForm[i];
        auto diff = finalTarget - projectiles[i]->GetPosition();
        auto dir = Vector3Normalize(diff);
        auto dist = Vector3Length(diff);
        // if (dist < 0.2f) continue;
        auto targetSpeed = TargetSpeed(dist, 5);
        auto targetVelocity = dir * targetSpeed;
        projectiles[i]->SetVelocity(targetVelocity);
    }
}
// Vector3 ParticlesForm::Target(Vector3 target, size_t i)
// {
//     auto diff = target + localCurentForm[i] - projectiles[i]->GetPosition();
//     auto dir = Vector3Normalize(diff);
//     auto dist = Vector3Length(diff);
//     auto targetSpeed = TargetSpeed(dist, 5);
//     auto targetVelocity = dir * targetSpeed;
//     return targetVelocity;
// }
