#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"

#include <stdio.h>

int main(int argc, char** argv)
{
    ma_result result;
    ma_engine engine;

    result = ma_engine_init(NULL, &engine);

    if (result != MA_SUCCESS) return -1;

    const char* filePath = argv[1];

    for (size_t i = 0; i < 8; i++)
    {
        ma_engine_play_sound(&engine, filePath, NULL);
        printf("sound\n");
        Sleep(100);
    }

    ma_engine_uninit(&engine);

    return 0;
}
