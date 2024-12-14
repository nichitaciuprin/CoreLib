#include "BaseLang.hpp"
#include "SysHelper.h"
#include "SysNet.h"

int main()
{
    SysNetUseAnyPort();

    char bytes[1024];
    uint64_t serverAddr = SysNetCreateAddr(127, 0, 0, 1, 27015);
    int messageSize;

    while (true)
    {
        const char* message = "fromclient";
        messageSize = strlen(message);
        strcpy(bytes, message);

        SysNetSend(&serverAddr, bytes, &messageSize);

        Halt(1000);

        SysNetRecv(&serverAddr, bytes, &messageSize);

        if (messageSize < 0)
        {
            Halt(1000);
            continue;
        }

        for (int i = 0; i < messageSize; i++)
            printf("%c", bytes[i]);
        printf("\n");

        Halt(1000);
    }

    return 0;
}
