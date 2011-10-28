#include "Actor.h"

namespace CGE
{
    Actor::Actor(Model* inModel) : mModel(inModel), mHead(NULL),
        mNextActor(NULL), mPreviousActor(NULL)
    {
    }

    Actor::~Actor()
    {
    }

    void Actor::removeFromBin()
    {
        if (mHead)
        {
            *mHead = mNextActor;
            if (mNextActor) mNextActor->mHead = mHead;
            mHead = NULL;
        }

        if (mPreviousActor) mPreviousActor->mNextActor = mNextActor;
        if (mNextActor) mNextActor->mPreviousActor = mPreviousActor;

        mPreviousActor = NULL;
        mNextActor = NULL;
    }
}
