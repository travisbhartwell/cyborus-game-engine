#ifndef SOUNDBUFFER_H
#define SOUNDBUFFER_H

#include "Audio.h"
#include <cstdlib>

namespace CGE
{
    class SoundBuffer
    {
        public:
            friend class SoundSource;

            SoundBuffer(const char* inFile = NULL);
            ~SoundBuffer();

            void loadFile(const char* inFile);
            void bindToSource(ALuint inSource) const;

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
