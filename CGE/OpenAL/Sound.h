#ifndef SOUND_H
#define SOUND_H

#include "alure.h"
#include <cstdlib>

namespace CGE
{
    class Sound
    {
        public:
            Sound(const char* inFile);
            ~Sound();

            void play();

            static void Setup(size_t inNumSources);
            static void Cleanup();

        protected:
        private:
            ALuint mHandle;

            struct ActiveSound
            {
                volatile bool isPlaying;
                bool isAttached;
                ALuint buffer;
            };

            static void finished(void* inData, ALuint inHandle);
            static size_t mNumSources;
            static size_t mCurrentSource;
            static ALuint* mSources;
            static ActiveSound* mActiveSounds;
    };
}

#endif
