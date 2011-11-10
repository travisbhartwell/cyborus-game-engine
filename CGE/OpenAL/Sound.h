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

            inline bool isFinished() const { return mFinished; }

            void play();

            static void Setup(size_t inNumSources);
            static void Cleanup();

        protected:
        private:
            ALuint mHandle;
            volatile bool mFinished;

            static void finished(void* inData, ALuint inHandle);
            static size_t mNumSources;
            static size_t mCurrentSource;
            static ALuint* mSources;
    };
}

#endif
