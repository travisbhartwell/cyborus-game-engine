#include "RenderBin.h"

namespace CGE
{
    RenderBin::RenderBin() : mHead(NULL)
    {
    }

    RenderBin::~RenderBin()
    {
    }

    void RenderBin::addActor(Actor* inActor)
    {
        if (!inActor) return;

        inActor->removeFromBin();

        if (mHead)
        {
            mHead->mHead = NULL;
            inActor->mNextActor = mHead;
        }

        mHead = inActor;
        inActor->mHead = &mHead;
    }

    void RenderBin::renderAll()
    {
        beforeRender();

        for (Actor* a = mHead; a; a = a->mNextActor)
            displayActor(a);

        afterRender();
    }

    void RenderBin::beforeRender()
    {
    }

    void RenderBin::afterRender()
    {
    }

    void RenderBin::displayActor(Actor* inActor)
    {
        inActor->display();
    }
}
