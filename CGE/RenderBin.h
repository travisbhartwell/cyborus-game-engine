#ifndef RENDERBIN_H
#define RENDERBIN_H

#include "Actor.h"

namespace CGE
{
    class RenderBin
    {
        public:
            RenderBin();
            virtual ~RenderBin();

            void addActor(Actor* inActor);
            void renderAll();

        protected:
            virtual void beforeRender();
            virtual void afterRender();
            virtual void displayActor(Actor* inActor);

        private:
            Actor* mHead;
    };
}

#endif
