#ifndef SOUNDSOURCE_H
#define SOUNDSOURCE_H

#include "SoundBuffer.h"
#include "../SceneGraphNode.h"

namespace CGE
{
    class SoundSource : public SceneGraphNode
    {
        public:
            SoundSource(const SoundBuffer& inSoundBuffer);
            virtual ~SoundSource();

            void update();
            bool isActive();

        protected:
        private:
            bool isPlaying();

            const SoundBuffer& mSoundBuffer;
            SourceBinding* mSourceBinding;
            bool mStarted;
    };
}

#endif
