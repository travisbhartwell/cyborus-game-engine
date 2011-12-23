#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include <cstdlib>

namespace CGE
{
    class Widget;

    typedef void (*Listener)(Widget*, void*);

    class EventListener
    {
        public:
            EventListener();
            ~EventListener();

            void configure(Listener inListener, void* inData = NULL);
            void dispatch(Widget* inWidget);

        protected:
        private:
            Listener mListener;
            void* mData;
    };
}

#endif
