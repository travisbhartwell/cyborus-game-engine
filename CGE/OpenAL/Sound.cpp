#include "Sound.h"

#include <cassert>
#include <cstring>
#include <iostream>
using namespace std;

namespace CGE
{
    size_t Sound::mNumSources = 0;
    size_t Sound::mCurrentSource = 0;
    ALuint* Sound::mSources = NULL;
    Sound::ActiveSound* Sound::mActiveSounds = NULL;

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
                mActiveSounds = new ActiveSound[mNumSources];
                memset(mActiveSounds, 0, mNumSources * sizeof(ActiveSound));
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
            delete [] mActiveSounds;
            mActiveSounds = NULL;
            mNumSources = 0;
        }
    }

    Sound::Sound(const char* inFile) : mHandle(0)
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
        if (!mHandle) return;

        ActiveSound* openSlot = NULL;
        for (size_t i = 0; i < mNumSources; ++i)
        {
            mCurrentSource = (mCurrentSource + 1) % mNumSources;

            ActiveSound& as = mActiveSounds[mCurrentSource];
            if (!as.isPlaying)
            {
                if (as.isAttached)
                {
                    alSourcei(mSources[mCurrentSource], AL_BUFFER, 0);
                    as.isAttached = false;
                    as.buffer = 0;
                }

                openSlot = &as;
                break;
            }
        }

        if (openSlot)
        {
            alSourcei(mSources[mCurrentSource], AL_BUFFER, mHandle);

            if (alurePlaySource(mSources[mCurrentSource], finished,
                mActiveSounds + mCurrentSource) == AL_FALSE)
            {
                cerr << "failed to start source\n";
            }
            else
            {
                openSlot->isPlaying = true;
                openSlot->isAttached = true;
                openSlot->buffer = mHandle;
            }
        }
        else
        {
            cerr << "no open audio sources\n";
        }
    }

    void Sound::finished(void* inData, ALuint inHandle)
    {
        ActiveSound* as = reinterpret_cast<ActiveSound*>(inData);
        assert(as != NULL);
        as->isPlaying = false;
    }
}
