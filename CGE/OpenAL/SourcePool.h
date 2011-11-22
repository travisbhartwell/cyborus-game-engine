#ifndef SOURCEPOOL_H
#define SOURCEPOOL_H

#include "Audio.h"
#include <cstdlib>

namespace CGE
{
    class SourcePool
    {
        public:
            SourcePool(size_t inSize);
            ~SourcePool();

        protected:
        private:
            ALuint* mHandles;
            size_t mSize;
    };
}

#endif
