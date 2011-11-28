#include "Audio.h"
#include <iostream>

namespace CGE
{
    static ALCdevice* device = NULL;
    static ALCcontext* context = NULL;
    static ALuint* sources = NULL;
    static SourceBinding* bindings = NULL;
    static size_t numSources = 0;

    void setupAudio(size_t inNumSources)
    {
        if (inNumSources > 0 && !isAudioActive())
        {
            device = alcOpenDevice(NULL);

            if (device)
            {
                context = alcCreateContext(device, NULL);

                if (context)
                {
                    alcMakeContextCurrent(context);
                    std::cerr << "-- OpenAL is working! --\n";

                    numSources = inNumSources;
                    sources = new ALuint[numSources];

                    alGenSources(numSources, sources);

                    bindings = new SourceBinding[numSources];
                    for (size_t i = 0; i < numSources; ++i)
                    {
                        SourceBinding& sb = bindings[i];
                        sb.source = sources[i];
                        sb.buffer = 0;
                        sb.canBeInterrupted = true;
                    }
                }
                else
                {
                    std::cerr << "-- error on alcCreateContext --\n";
                    cleanupAudio();
                }
            }
            else
            {
                std::cerr << "-- error on alcOpenDevice --\n";
                cleanupAudio();
            }
        }
    }

    void cleanupAudio()
    {
        if (context)
        {
            alDeleteSources(numSources, sources);
            delete [] sources;
            delete [] bindings;
            sources = NULL;
            numSources = 0;

            alcMakeContextCurrent(NULL);
            alcDestroyContext(context);
        }

        if (device)
        {
            alcCloseDevice(device);
            std::cerr << "-- closed OpenAL device --\n";
        }
    }

    bool isAudioActive()
    {
        return !!context;
    }

    SourceBinding* requestAudioSource()
    {
        for (size_t i = 0; i < numSources; ++i)
        {
            SourceBinding* sb = bindings + i;
            if (!sb->buffer) return sb;
        }

        return NULL;
    }
}
