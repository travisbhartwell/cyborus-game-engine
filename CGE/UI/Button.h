#ifndef BUTTON_H
#define BUTTON_H

#include "../Image.h"
#include "../OpenGL/Texture2D.h"
#include "../OpenGL/InterleavedVBO.h"
#include "Widget.h"

namespace CGE
{
    class Button : public Widget
    {
        public:
            Button(const Image& inImage, float inWidth, float inHeight);
            virtual ~Button();

            void setPosition(float inX, float inY);

            virtual void display();

            virtual void onMouseIn(bool inIsClickCandidate);
            virtual void onMouseOut();
            virtual void onMouseDown();
            virtual void onMouseUp();

        protected:
        private:
            Texture2D mTexture;
            InterleavedVBO mVBO;
            GLint mFirst;
    };
}

#endif
