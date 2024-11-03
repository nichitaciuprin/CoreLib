#include "SysHelper.h"
#include "SysNet.h"
#include "BaseExt.h"
#include "Subgen.h"
#include "Helper.h"
#include "Models.h"
#include "Clipping.h"
#include "Bitmap.h"

#include "ServerClient.h"
#include "Server.h"

// #include "SysWindow.h"

int main(int argc, char** argv)
{
    printf("PID %ld\n", (long)GetPid());

    NetInitServer(argc, argv);

    Halt(3000);

    InitGame();

    while (true)
    {
        FixedTimeStart();

        // TestRender();

        RenderGame();
        UpdateGame(0.010f);

        FixedTimeEnd();
    }

    return 0;
}
