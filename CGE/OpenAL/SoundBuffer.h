#ifndef SOUNDBUFFER_H
#define SOUNDBUFFER_H

#include "Audio.h"
#include <cstdlib>

namespace CGE
{
    class SoundBuffer
    {
        public:
            SoundBuffer(const char* inFile = NULL);
            ~SoundBuffer();

            void loadFile(const char* inFile);

        protected:
        private:
            SoundBuffer(const SoundBuffer& inSoundBuffer)
            {
                // no copying
            }

            SoundBuffer& operator=(const SoundBuffer& inSoundBuffer)
            {
                // no copying
                return *this;
            }

            ALuint mHandle;
    };
}

#endif
