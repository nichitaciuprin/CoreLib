#include "BaseExt.h"
#include "SysHelper.h"
#include "Window.h"
#include "ServerClient.h"

int main(int argc, char** argv)
{
    printf("PID %ld\n", (long)GetPid());

    NetInitClient(argc, argv);

    int x, y;
    GetConsolePosition(&x, &y);

    auto window = make_unique<Window>(x, y, 512, 512);

    // missing memset to render stack, for fun
    char frame[1024];

    while (true)
    {
        FixedTimeStart();

        if (!window->Exists()) break;

        window->Update();
        window->SetPixelsScaled2((uint8_t*)frame, 32, 32, 16);

        while (SysNetRecvFrame(frame)) {}

        NetInput netInput = {};

        netInput.w = window->KeyDown_W();
        netInput.a = window->KeyDown_A();
        netInput.s = window->KeyDown_S();
        netInput.d = window->KeyDown_D();

        netInput.up = window->KeyDown_UP();
        netInput.left = window->KeyDown_LEFT();
        netInput.down = window->KeyDown_DOWN();
        netInput.right = window->KeyDown_RIGHT();

        netInput.q = window->KeyDown_Q();
        netInput.e = window->KeyDown_E();

        SysNetSendInput(&netInput);

        FixedTimeEnd();
    }

    return 0;
}
