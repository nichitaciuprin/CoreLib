#pragma once

#include "SysNet.h"

struct NetInput
{
    bool w, a, s, d;
    bool up, left, down, right;
    bool q, e;
};

void NetInitServer(int argc, char** argv)
{
    int32_t port = argc == 2 ? strtol(argv[1], NULL, 10) : 27015;
    SysNetUsePort(port);
}
inline void SysNetSendFrame(uint64_t* addr, char* frame)
{
    int messageSize = 1024;
    SysNetSend(addr, frame, &messageSize);
}
inline bool SysNetRecvInput(uint64_t* addr, NetInput* input)
{
    char buffer[1024];
    int messageSize = 0;

    SysNetRecv(addr, buffer, &messageSize);

    if (messageSize < 0) return false;

    *input = {};

    uint8_t byte1 = ((uint8_t*)buffer)[0];
    uint8_t byte2 = ((uint8_t*)buffer)[1];

    input->w     = (1 << 7 & byte1) != 0;
    input->a     = (1 << 6 & byte1) != 0;
    input->s     = (1 << 5 & byte1) != 0;
    input->d     = (1 << 4 & byte1) != 0;
    input->up    = (1 << 3 & byte1) != 0;
    input->left  = (1 << 2 & byte1) != 0;
    input->down  = (1 << 1 & byte1) != 0;
    input->right = (1 << 0 & byte1) != 0;

    input->q  = (1 << 7 & byte2) != 0;
    input->e  = (1 << 6 & byte2) != 0;

    return true;
}

static uint64_t _serverAddr;
void NetInitClient(int argc, char** argv)
{
    SysNetUseAnyPort();

    if (argc == 1)
    {
        cout << "Try CampfireClient.exe servername"     << endl;
        cout << "   localhost -> 127.0.0.1:27015"       << endl;
        cout << "   shells    -> 168.100.238.173:27015" << endl;
        cout << "   azure     -> 20.215.34.35:27015"    << endl;
        cout << "   machine1  -> 89.28.71.195:27015"    << endl;
        cout << "   machine2  -> 89.28.87.65:49161"     << endl;

        _serverAddr = SysNetCreateAddr(127, 0, 0, 1, 27015);
    }
    if (argc == 2)
    {
        int option;

        if (strcmp(argv[1], "localhost") == 0) option = 0; else
        if (strcmp(argv[1], "shells")    == 0) option = 1; else
        if (strcmp(argv[1], "azure")     == 0) option = 2; else
        if (strcmp(argv[1], "machine1")  == 0) option = 3; else
        if (strcmp(argv[1], "machine2")  == 0) option = 4; else
        abort();

        switch (option)
        {
            case 0: cout << "localhost -> 127.0.0.1:27015"     << endl; _serverAddr = SysNetCreateAddr(127,   0,   0,   1, 27015); break;
            case 1: cout << "shells -> 168.100.238.173:27015"  << endl; _serverAddr = SysNetCreateAddr(168, 100, 238, 173, 27015); break;
            case 2: cout << "azure -> 20.215.34.35:27015"      << endl; _serverAddr = SysNetCreateAddr( 20, 215,  34,  35, 27015); break;
            case 3: cout << "machine1 -> 89.28.71.195:27015"   << endl; _serverAddr = SysNetCreateAddr( 89,  28,  71, 195, 27015); break;
            case 4: cout << "machine2 -> 89.28.87.65:49161"    << endl; _serverAddr = SysNetCreateAddr( 89,  28,  87,  65, 49161); break;
            default: abort();
        }
    }
}
inline bool SysNetRecvFrame(char* frame)
{
    int messageSize = 0;

    uint64_t addr;

    SysNetRecv(&addr, frame, &messageSize);

    if (messageSize < 0) return false;

    return true;
}
inline void SysNetSendInput(NetInput* input)
{
    uint8_t bytes[2] = {};
    // uint8_t message2 = 0;

    if (input->w)     bytes[0] += 128;
    if (input->a)     bytes[0] +=  64;
    if (input->s)     bytes[0] +=  32;
    if (input->d)     bytes[0] +=  16;
    if (input->up)    bytes[0] +=   8;
    if (input->left)  bytes[0] +=   4;
    if (input->down)  bytes[0] +=   2;
    if (input->right) bytes[0] +=   1;

    if (input->q)     bytes[1] +=  128;
    if (input->e)     bytes[1] +=   64;

    // if (input->w) message += 2;
    // if (input->a) message += 1;

    int messageSize = 2;

    SysNetSend(&_serverAddr, (char*)&bytes, &messageSize);
}
