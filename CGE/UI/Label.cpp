#include "Label.h"

namespace CGE
{
    Label::Label(const Image& inImage, float inWidth, float inHeight)
    {
        mTexture.loadImage(inImage);

        const float Min = 0.1f;
        if (inWidth < Min) inWidth = Min;
        if (inHeight < Min) inHeight = Min;

        mRadiusX = inWidth / 2.0f;
        mRadiusY = inHeight / 2.0f;

        mClusterVBO.mount(mVertexVBO, 0);
        mClusterVBO.mount(mTextureVBO, 1);

        GLfloat vertices[4 * 2];
        GLfloat* vertex = vertices;

        GLfloat texCoords[4 * 2];
        GLfloat* texCoord = texCoords;

        *vertex++ = mRadiusX;
        *vertex++ = mRadiusY;
        *texCoord++ = 1.0f;
        *texCoord++ = 0.0f;

        *vertex++ = mRadiusX;
        *vertex++ = -mRadiusY;
        *texCoord++ = 1.0f;
        *texCoord++ = 1.0f;

        *vertex++ = -mRadiusX;
        *vertex++ = -mRadiusY;
        *texCoord++ = 0.0f;
        *texCoord++ = 1.0f;

        *vertex++ = -mRadiusX;
        *vertex++ = mRadiusY;
        *texCoord++ = 0.0f;
        *texCoord++ = 0.0f;

        mVertexVBO.loadData(vertices, 4, 2);
        mTextureVBO.loadData(texCoords, 4, 2);

        setPosition(0.0f, 0.0f);
    }

    Label::~Label()
    {
            //dtor
    }
    /** @brief display
      *
      * @todo: document this function
      */

    void Label::display()
    {
        mTexture.bind();
        mClusterVBO.display(GL_TRIANGLE_FAN, 0, 4);
    }

    /** @brief setPosition
      *
      * @todo: document this function
      */
    void Label::setPosition(float inX, float inY)
    {
        mX = inX;
        mY = inY;

        mTransform.loadIdentity();
        mTransform.translate(mX, mY, 0.0f);
    }

}
