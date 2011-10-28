#include "InterleavedVBO.h"
#include <cassert>

namespace CGE
{
    InterleavedVBO::InterleavedVBO() : mVertexSize(0), mNumMappings(0)
    {
        memset(mMappings, 0, sizeof(mMappings));
        glGenBuffers(1, &mHandle);
    }

    InterleavedVBO::~InterleavedVBO()
    {
        glDeleteBuffers(1, &mHandle);
    }

    void InterleavedVBO::addField(GLuint inIndex, GLuint inSize)
    {
        assert(inSize > 0);
        assert(mNumMappings < MaxMappings);

        mVertexSize += inSize * sizeof(GLfloat);
        mMappings[mNumMappings].index = inIndex;
        mMappings[mNumMappings].size = inSize;

        ++mNumMappings;

        assert(mVertexSize > 0);
    }

    void InterleavedVBO::loadData(GLvoid* inData, GLuint inSize)
    {
        mNumVertices = inSize;

        bind();
        glBufferData(GL_ARRAY_BUFFER, mNumVertices * mVertexSize, inData,
            GL_STATIC_DRAW);
    }

    void InterleavedVBO::enableVAA()
    {
        bind();

        size_t offset = 0;
        for (size_t i = 0; i < mNumMappings; ++i)
        {
            FieldMapping& m = mMappings[i];
            glVertexAttribPointer(m.index, m.size, GL_FLOAT, GL_FALSE,
                mVertexSize, bufferOffset(offset));
            glEnableVertexAttribArray(m.index);

            offset += m.size * sizeof(GLfloat);
        }
    }

    void InterleavedVBO::disableVAA()
    {
        for (size_t i = 0; i < mNumMappings; ++i)
        {
            FieldMapping& m = mMappings[i];
            glDisableVertexAttribArray(m.index);
        }
    }

    void InterleavedVBO::display(const IndexVBO& inIVBO, GLenum inMode)
    {
        enableVAA();
        inIVBO.draw(inMode);
        disableVAA();
    }

    void InterleavedVBO::display(GLenum inMode, GLint inFirst, GLsizei inCount)
    {
        enableVAA();
        glDrawArrays(inMode, inFirst, inCount);
        disableVAA();
    }
}
