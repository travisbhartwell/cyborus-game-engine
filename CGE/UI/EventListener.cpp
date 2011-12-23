#include "EventListener.h"

namespace CGE
{
    EventListener::EventListener() : mListener(NULL), mData(NULL)
    {
    }

    EventListener::~EventListener()
    {
    }

    void EventListener::configure(Listener inListener, void* inData)
    {
        mListener = inListener;
        mData = inData;
    }

    void EventListener::dispatch(Widget* inWidget)
    {
        if (mListener) mListener(inWidget, mData);
    }
}
