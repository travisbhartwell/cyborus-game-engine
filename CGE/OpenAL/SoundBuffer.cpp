#include "SoundBuffer.h"

#include <cstdio>
#include <iostream>
#include <ogg/ogg.h>
#include <vorbis/codec.h>
#include <vorbis/vorbisenc.h>
#include <vorbis/vorbisfile.h>

namespace CGE
{
    SoundBuffer::SoundBuffer(const char* inFile) : mHandle(0)
    {
        if (alcGetCurrentContext())
        {
            std::cerr << "found context -- generating buffer\n";
            alGenBuffers(1, &mHandle);
            loadFile(inFile);
        }
        else
        {
            std::cerr << "no context\n";
        }
    }

    SoundBuffer::~SoundBuffer()
    {
        if (mHandle) alDeleteBuffers(1, &mHandle);
    }

    void SoundBuffer::loadFile(const char* inFile)
    {
        if (!inFile || !*inFile) return;

        FILE* f = fopen(inFile, "rb");
        if (!f)
        {
            std::cerr << "failed to open audio file: " << inFile << '\n';
            return;
        }

        OggVorbis_File ovf;
        int result = ov_open(f, &ovf, NULL, 0);
        if (result < 0)
        {
            // We only need to close the file if and only if ov_open fails.
            // http://xiph.org/vorbis/doc/vorbisfile/ov_open.html
            fclose(f);
            std::cerr << "failed to open ogg file: " << inFile << '\n';
            return;
        }

        vorbis_info* vorbisInfo = ov_info(&ovf, -1);
        vorbis_comment* vorbisComment = ov_comment(&ovf, -1);

        ALenum format = vorbisInfo->channels == 1 ? AL_FORMAT_MONO16
            : AL_FORMAT_STEREO16;

        const size_t BufferSize = 4096 * 64;
        void* chunk = malloc(BufferSize);
        char* data = reinterpret_cast<char*>(chunk);

        int got = 0;
        int bytes = BufferSize;
        while (bytes > 0)
        {
            int section;
            result = ov_read(&ovf, data + got, bytes, 0, 2, 1, &section);

            if (result <= 0) break;

            bytes -= result;
            got += result;
        }

        alBufferData(mHandle, format, data, got, vorbisInfo->rate);

        free(chunk);
    }
}
