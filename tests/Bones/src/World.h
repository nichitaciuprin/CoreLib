struct Input
{
    Vector2 wasd;
    Vector2 mouseDelta;
    bool key1;
    bool key2;
    bool key3;
    bool key4;
};

class World
{
    friend class Renderer;

public:
    World();
    void Update(Input input, float deltaTime);
    void Render();

private:
    float timer1;
    Subgen subgen;
    Camera camera;
    unique_ptr<WorldPhysics> worldPhysics;
    vector<unique_ptr<Enemy>> enemies;
    unique_ptr<StaticBound> ground;
    vector<shared_ptr<Projectile>> projectiles;
    bool gather = false;

    void SpawnEnemy();
    void UpdatePlayer(Input input, float deltaTime);
    void UpdateEnemies(float deltaTime);
    void SpawnProjectile();
    void PushEnemies();
};
