struct Player
{
    uint64_t id;
    float timer;
    Camera camera;
};

#define PLAYER_MAX_SIZE 16

unique_ptr<Bitmap> bitmapNet;
vector<Player> players;

void DestroyPlayers(float deltaTime)
{
    for (int i = players.size() - 1; i >= 0; i--)
    {
        auto& player = players[i];
        player.timer -= deltaTime;
        if (player.timer <= 0)
        {
            cout << "Player disconnected ";
            SysNetPrintAddr(player.id);
            cout << endl;

            erase_back(players, i);
        }
    }
}
void UpdatePlayer(uint64_t playerAddr, NetInput& input)
{
    for (size_t i = 0; i < players.size(); i++)
    {
        auto& player = players[i];

        if (player.id == playerAddr)
        {
            player.timer = 10;

            bool w = input.w;
            bool a = input.a;
            bool s = input.s;
            bool d = input.d;
            bool up    = input.up;
            bool left  = input.left;
            bool down  = input.down;
            bool right = input.right;
            bool e = input.e;
            bool q = input.q;

            UpdateCameraRotation(&player.camera, 0.023f, left, up, down, right);
            UpdateCameraPosition(&player.camera, 0.008f, w, a, s, d, e, q);

            return;
        }
    }

    if (players.size() == PLAYER_MAX_SIZE) return;

    // cout << recvInput.id << endl;

    cout << "Player connected ";
    SysNetPrintAddr(playerAddr);
    cout << endl;

    Player player = {};
    player.id = playerAddr;
    player.timer = 10;
    player.camera = { 0, 1, 95 };
    players.push_back(player);
}

void Draw(Bitmap& bitmap, Player& player, long time)
{
    bitmap.Reset();

    auto view = MatrixView3(&player.camera);

    for (auto& i : players)
    {
        if (player.id == i.id) continue;
        bitmap.DrawCubeTemp(i.camera.position, {}, player.camera, COLOR_RED);
    }

    {
        Vector3 p0 = { -1, 0,  2 }; p0 *= view;
        Vector3 p1 = { -1, 0, 95 }; p1 *= view;
        Vector3 p2 = {  1, 0, 95 }; p2 *= view;
        Vector3 p3 = {  1, 0,  2 }; p3 *= view;
        bitmap.DrawPoligon1(p0, p1, p2, p3, COLOR_WHITE);
    }
    {
        float size = 5;
        Vector3 p0 = { -size, 0, -size + 100 }; p0 *= view;
        Vector3 p1 = { -size, 0,  size + 100 }; p1 *= view;
        Vector3 p2 = {  size, 0,  size + 100 }; p2 *= view;
        Vector3 p3 = {  size, 0, -size + 100 }; p3 *= view;
        bitmap.DrawPoligon1(p0, p1, p2, p3, COLOR_WHITE);
    }

    // TODO fix this
    // bitmap->ApplyBlackWhiteColorDepth();

    {
        auto time2 = (float)time / 600;
        Vector3 position = { 0, 0.5f, 100 };
        Vector3 rotation = { 0, time2, 0 };
        Vector3 scale = { 1, 1, 1 };
        auto world = MatrixWorld2(position, rotation, scale);
        bitmap.DrawCubeColored(world * view);
    }
    {
        auto time2 = (float)time / 300;
        Vector3 position = { 0, 1.5f, 100 };
        Vector3 rotation = { 0, time2, 0 };
        Vector3 scale = { 1, 1, 1 };
        auto world = MatrixWorld2(position, rotation, scale);
        bitmap.DrawCubeColored(world * view);
    }
}
void Draw(Bitmap& bitmap, Camera camera, long time)
{
    bitmap.Reset();

    for (auto& i : players)
        bitmap.DrawCubeTemp(i.camera.position, {}, camera, COLOR_RED);

    auto view = MatrixView3(&camera);

    {
        Vector3 p0 = { -1, 0,  2 }; p0 *= view;
        Vector3 p1 = { -1, 0, 95 }; p1 *= view;
        Vector3 p2 = {  1, 0, 95 }; p2 *= view;
        Vector3 p3 = {  1, 0,  2 }; p3 *= view;
        bitmap.DrawPoligon1(p0, p1, p2, p3, COLOR_WHITE);
    }
    {
        float size = 5;
        Vector3 p0 = { -size, 0, -size + 100 }; p0 *= view;
        Vector3 p1 = { -size, 0,  size + 100 }; p1 *= view;
        Vector3 p2 = {  size, 0,  size + 100 }; p2 *= view;
        Vector3 p3 = {  size, 0, -size + 100 }; p3 *= view;
        bitmap.DrawPoligon1(p0, p1, p2, p3, COLOR_WHITE);
    }

    // TODO fix this
    // bitmap->ApplyBlackWhiteColorDepth();

    {
        auto time2 = (float)time / 600;
        Vector3 position = { 0, 0.5f, 100 };
        Vector3 rotation = { 0, time2, 0 };
        Vector3 scale = { 1, 1, 1 };
        auto world = MatrixWorld2(position, rotation, scale);
        bitmap.DrawCubeColored(world * view);
    }
    {
        auto time2 = (float)time / 300;
        Vector3 position = { 0, 1.5f, 100 };
        Vector3 rotation = { 0, time2, 0 };
        Vector3 scale = { 1, 1, 1 };
        auto world = MatrixWorld2(position, rotation, scale);
        bitmap.DrawCubeColored(world * view);
    }
}

void InitGame()
{
    // auto scale = 16;
    auto size1 = 32;
    // auto size2 = 32*scale;

    bitmapNet = make_unique<Bitmap>(size1, size1);

    players = vector<Player>();
    players.reserve(PLAYER_MAX_SIZE);
}

void RenderGame()
{
    for (auto& player : players)
    {
        Draw(*bitmapNet, player, GetTime());

        char buffer[1024];

        for (int i = 0; i < 1024; i++)
            buffer[i] = ColorToLightValue(bitmapNet->pixels[i]);

        SysNetSendFrame(&player.id, buffer);
    }
}
void UpdateGame(float deltaTime)
{
    DestroyPlayers(deltaTime);

    uint64_t addr;
    NetInput netInput;

    while (SysNetRecvInput(&addr, &netInput))
    {
        UpdatePlayer(addr, netInput);
    }
}

// unique_ptr<Bitmap> testBitmap;
// unique_ptr<Window> testWindow;
// bool TestRenderCalled = false;
// void TestRender()
// {
//     if (!TestRenderCalled)
//     {
//         TestRenderCalled = true;

//         int x, y;
//         GetConsolePosition(&x, &y);

//         testBitmap = make_unique<Bitmap>(512, 512);
//         testWindow = make_unique<Window>(x, y, 512, 512);

//         return;
//     }

//     Camera camera = { 0, 1, 95 };
//     Draw(*testBitmap, camera, GetTime());
//     // testBitmap->FillBorder(COLOR_GREEN);
//     testWindow->SetPixels(testBitmap->pixels.data(), 32*16, 32*16);
//     testWindow->Update();
// }
