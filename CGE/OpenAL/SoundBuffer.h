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
            void loadOgg(const char* inFile);
            void loadWav(const char* inFile);

            ALuint mHandle;

            SoundBuffer(const SoundBuffer& inSoundBuffer)
            {
                // no copying
            }

            SoundBuffer& operator=(const SoundBuffer& inSoundBuffer)
            {
                // no copying
                return *this;
            }
    };
}

#endif
