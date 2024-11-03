#include <stdio.h>
#include <alsa/asoundlib.h>

void PrintParamInfo(snd_pcm_t* pcm_handle, snd_pcm_hw_params_t* params)
{
    const char* pcmName = snd_pcm_name(pcm_handle);
    const char* pcmState = snd_pcm_state_name(snd_pcm_state(pcm_handle));

    unsigned int channels;
    unsigned int rate;

    snd_pcm_hw_params_get_channels(params, &channels);
    snd_pcm_hw_params_get_rate(params, &rate, 0);

    printf("pcm name: %s\n", pcmName);
    printf("pcm state: %s\n", pcmState);

    printf("channels: %i ", channels);
    if      (channels == 1) printf("(mono)\n");
    else if (channels == 2) printf("(stereo)\n");
    else                    printf("(!!!!!!!!)\n");

    printf("rate: %d bps\n", rate);
}

int main(int argc, char** argv)
{
    unsigned int pcm;
    snd_pcm_t* pcm_handle;
    snd_pcm_hw_params_t* params;

    unsigned int rate = atoi(argv[1]);
    int channels      = atoi(argv[2]);

    const char* pcmName = "default";

    // Open the PCM device in playback mode
    pcm = snd_pcm_open(&pcm_handle, pcmName, SND_PCM_STREAM_PLAYBACK, 0);
    if (pcm < 0)
        printf("ERROR: Can't open \"%s\" PCM device. %s\n", pcmName, snd_strerror(pcm));

    // Allocate parameters object and fill it with default values
    snd_pcm_hw_params_alloca(&params);

    snd_pcm_hw_params_any(pcm_handle, params);

    // Set parameters
    pcm = snd_pcm_hw_params_set_access(pcm_handle, params, SND_PCM_ACCESS_RW_INTERLEAVED);
    if (pcm < 0)
        printf("ERROR: Can't set interleaved mode. %s\n", snd_strerror(pcm));

    pcm = snd_pcm_hw_params_set_format(pcm_handle, params, SND_PCM_FORMAT_S16_LE);
    if (pcm < 0)
        printf("ERROR: Can't set format. %s\n", snd_strerror(pcm));

    pcm = snd_pcm_hw_params_set_channels(pcm_handle, params, channels);
    if (pcm < 0)
        printf("ERROR: Can't set channels number. %s\n", snd_strerror(pcm));

    pcm = snd_pcm_hw_params_set_rate_near(pcm_handle, params, &rate, 0);
    if (pcm < 0)
        printf("ERROR: Can't set rate. %s\n", snd_strerror(pcm));

    // Write parameters
    pcm = snd_pcm_hw_params(pcm_handle, params);
    if (pcm < 0)
        printf("ERROR: Can't set hardware parameters. %s\n", snd_strerror(pcm));

    PrintParamInfo(pcm_handle, params);

    snd_pcm_uframes_t frames;
    unsigned int periodTime;
    snd_pcm_hw_params_get_period_size(params, &frames, 0);
    snd_pcm_hw_params_get_period_time(params, &periodTime, NULL);

    printf("frames %i\n", frames);

    // Allocate buffer to hold single period
    int buffSize = frames * channels * 2;
    char* buff = (char*)malloc(buffSize);

    size_t loops = (seconds * 1000000) / periodTime;

    for (size_t i = 0; i < 30; i++)
    {
        pcm = read(0, buff, buffSize);

        printf("%i\n", pcm);

        pcm = snd_pcm_writei(pcm_handle, buff, frames);

        if (pcm == -EPIPE)
        {
            printf("XRUN.\n");
            snd_pcm_prepare(pcm_handle);
        }
        else if (pcm < 0)
        {
            printf("ERROR. Can't write to PCM device. %s\n", snd_strerror(pcm));
        }
    }

    snd_pcm_drain(pcm_handle);
    snd_pcm_close(pcm_handle);

    free(buff);

    return 0;
}
