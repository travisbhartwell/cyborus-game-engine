#include "SoundSource.h"

namespace CGE
{
    SoundSource::SoundSource(const SoundBuffer& inSoundBuffer)
        : mSoundBuffer(inSoundBuffer), mSourceBinding(NULL), mStarted(false)
    {
    }

    SoundSource::~SoundSource()
    {
    }

    void SoundSource::update()
    {
        if (!mStarted)
        {
            mStarted = true;
            mSourceBinding = requestAudioSource();

            if (mSourceBinding)
            {
                mSourceBinding->buffer = mSoundBuffer.mHandle;
                alSourcei(mSourceBinding->source, AL_BUFFER,
                    mSourceBinding->buffer);
                alSourcePlay(mSourceBinding->source);
            }
        }
        else if (!isPlaying() && isActive())
        {
            alSourcei(mSourceBinding->source, AL_BUFFER, 0);
            mSourceBinding->buffer = 0;
            mSourceBinding = NULL;
        }
    }

    bool SoundSource::isActive()
    {
        return mSourceBinding
            && mSourceBinding->buffer == mSoundBuffer.mHandle;
    }

    bool SoundSource::isPlaying()
    {
        if (isActive())
        {
            int result;
            alGetSourcei(mSourceBinding->source, AL_SOURCE_STATE, &result);
            return result == AL_PLAYING;
        }

        return false;
    }
}
