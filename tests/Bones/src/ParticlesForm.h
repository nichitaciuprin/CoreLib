class ParticlesForm
{
public:
    Vector3 localInitForm[9] = {};
    Vector3 localCurentForm[9] = {};
    Vector3 localTargetForm[9] = {};
    Vector3 finalForm[9] = {};

    ParticlesForm();
    void Update(float deltaTime, Subgen* subgen, Vector3 target, vector<shared_ptr<Projectile>>& projectiles);

private:
    float timer = 0;
};
