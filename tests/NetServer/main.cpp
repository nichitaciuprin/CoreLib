#include "BaseExt.h"
#include "SysHelper.h"
#include "SysNet.h"

int main()
{
    SysNetUsePort(27015);

    char bytes[1024];
    uint64_t serverAddr;
    int messageSize;

    while (true)
    {
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

        const char* message = "fromserver";
        int messageSize = strlen(message);
        strcpy(bytes, message);

        SysNetSend(&serverAddr, bytes, &messageSize);

        Halt(1000);
    }

    return 0;
}
