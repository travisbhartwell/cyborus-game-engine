#include "SourcePool.h"

namespace CGE
{
    SourcePool::SourcePool(size_t inSize) : mHandles(NULL), mSize(inSize)
    {
        if (mSize < 1) mSize = 8;
        mHandles = new ALuint[mSize];
        alGenSources(mSize, mHandles);
    }

    SourcePool::~SourcePool()
    {
        alDeleteSources(mSize, mHandles);
        delete [] mHandles;
    }
}
