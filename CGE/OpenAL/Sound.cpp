#include "Sound.h"

#include <cassert>
#include <iostream>
using namespace std;

namespace CGE
{
    size_t Sound::mNumSources = 0;
    size_t Sound::mCurrentSource = 0;
    ALuint* Sound::mSources = NULL;

    void Sound::Setup(size_t inNumSources)
    {
        if (inNumSources && !mNumSources)
        {
            mNumSources = inNumSources;
            mSources = new ALuint[mNumSources];
            alGenSources(mNumSources, mSources);

            if (alGetError() != AL_NO_ERROR)
            {
                cerr << "failure to setup OpenAL sources\n";
                delete [] mSources;
                mSources = NULL;
                mNumSources = 0;
            }
            else
            {
                cerr << "OpenAL working!\n";
            }
        }
        else
        {
            cerr << "something blocked OpenAL setup\n";
        }
    }

    void Sound::Cleanup()
    {
        if (mSources && mNumSources)
        {
            alDeleteSources(mNumSources, mSources);
            delete [] mSources;
            mSources = NULL;
            mNumSources = 0;
        }
    }

    Sound::Sound(const char* inFile) : mHandle(0), mFinished(true)
    {
        assert(inFile && *inFile);
        mHandle = alureCreateBufferFromFile(inFile);
        if (!mHandle)
        {
            cerr << "failed to load " << inFile << ": "
                << alureGetErrorString() << '\n';
        }
    }

    Sound::~Sound()
    {
        if (mHandle) alDeleteBuffers(1, &mHandle);
    }

    void Sound::play()
    {
        mCurrentSource = (mCurrentSource + 1) % mNumSources;
        alSourcei(mSources[mCurrentSource], AL_BUFFER, mHandle);

        if (alurePlaySource(mSources[mCurrentSource], finished, this)
            == AL_FALSE)
        {
            cerr << "failed to start source\n";
            mFinished = true;
        }
        else
        {
            mFinished = false;
        }
    }

    void Sound::finished(void* inData, ALuint inHandle)
    {
        Sound* s = reinterpret_cast<Sound*>(inData);

        assert(s != NULL);
        assert(inHandle == s->mHandle);

        s->mFinished = true;
    }
}
