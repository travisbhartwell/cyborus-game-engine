#ifndef LABEL_H
#define LABEL_H

#include "../Image.h"
#include "../OpenGL/Texture2D.h"
#include "../OpenGL/ClusterVBO.h"
#include "Widget.h"

namespace CGE
{
    class Label : public Widget
    {
        public:
            Label(const Image& inImage, float inWidth, float inHeight);
            virtual ~Label();

            void setPosition(float inX, float inY);

            virtual void display();

        protected:
        private:
            Texture2D mTexture;
            VertexBufferObject mVertexVBO;
            VertexBufferObject mTextureVBO;
            ClusterVBO mClusterVBO;
    };
}

#endif
