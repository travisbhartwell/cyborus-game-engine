#ifndef AUDIO_H
#define AUDIO_H

#ifdef __WIN32__
#   include <al.h>
#   include <alc.h>
#else
#   include <AL/al.h>
#   include <AL/alc.h>
#endif

#include <cstdlib>

namespace CGE
{
    struct SourceBinding
    {
        ALuint source;
        ALuint buffer;
        bool canBeInterrupted;
    };

    void setupAudio(size_t inNumSources);
    void cleanupAudio();
    bool isAudioActive();
    SourceBinding* requestAudioSource();
}

#endif
