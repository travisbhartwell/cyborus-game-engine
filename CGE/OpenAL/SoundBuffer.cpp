#include "SoundBuffer.h"
#include "../Tools.h"

#include <cstdio>
#include <cstring>
#include <iostream>
#include <fstream>
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

        const char* lastDot = NULL;
        for (const char* i = inFile; *i; ++i)
        {
            if (*i == '.') lastDot = i;
        }

        if (lastDot)
        {
            const char* extension = lastDot + 1;

            if (!stricmp(extension, "ogg"))
                loadOgg(inFile);
            else if (!stricmp(extension, "wav"))
                loadWav(inFile);
        }
        else
        {
            std::cerr << "found no audio file extension :(\n";
        }
    }

    void SoundBuffer::loadOgg(const char* inFile)
    {
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
        //vorbis_comment* vorbisComment = ov_comment(&ovf, -1);

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

    void SoundBuffer::loadWav(const char* inFile)
    {
        std::ifstream fin;
        fin.open(inFile, std::ifstream::binary);
        if (!fin)
        {
            std::cerr << "failed to open wav file: " << inFile << '\n';
            return;
        }

        std::cerr << "loading " << inFile << '\n';

        fin.seekg(0, std::ios_base::end);
        size_t size = fin.tellg();
        fin.seekg(0, std::ios_base::beg);

        if (size > 44)
        {
            char* buffer = new char[size];
            fin.read(buffer, size);

            if (!memcmp(buffer, "RIFF", 4)
                && !memcmp(buffer + 8, "WAVEfmt ", 8))
            {
                std::cerr << "allegedly a valid wav file!\n";

                short format;
                readBytes(buffer + 20, format);

                short channels;
                readBytes(buffer + 22, channels);

                int sampleRate;
                readBytes(buffer + 24, sampleRate);

                int byteRate;
                readBytes(buffer + 28, byteRate);

                short bitsPerSample;
                readBytes(buffer + 34, bitsPerSample);

                std::cerr << "format == " << format
                    << "\nchannels == " << channels
                    << "\nsample rate == " << sampleRate
                    << "\nbyte rate == " << byteRate
                    << "\nbits per sample == " << bitsPerSample
                    << '\n';

                size_t offset = 0;
                if (bitsPerSample != 16)
                {
                    short excess;
                    readBytes(buffer + 36, excess);
                    offset = excess;
                }

                if (memcmp(buffer + 36 + offset, "data", 4))
                {
                    std::cerr << "invalid WAV format: missing 'data' marker\n";
                }
                else
                {
                    int dataChunkSize;
                    readBytes(buffer + 40 + offset, dataChunkSize);

                    if (dataChunkSize > 0)
                    {
                        alBufferData(mHandle, format == 1 ? AL_FORMAT_MONO16
                            : AL_FORMAT_STEREO16, buffer + 44 + offset,
                            dataChunkSize, sampleRate);
                    }
                    else
                    {
                        std::cerr << "invalid WAV format: "
                            "bad data chunk size\n";
                    }
                }
            }
            else
            {
                std::cerr << "invalid WAV format: missing 'RIFF' header\n";
            }

            delete [] buffer;
        }
        else
        {
            std::cerr << "bad wav file size: " << size << '\n';
        }

        fin.close();
    }
}
