#ifndef VERTEXBUFFEROBJECT_H
#define VERTEXBUFFEROBJECT_H

#include "../Graphics.h"

namespace CGE
{
    class VertexBufferObject
    {
        public:
            friend class VertexArrayObject;
            friend class ClusterVBO;

            VertexBufferObject(GLenum inTarget = GL_ARRAY_BUFFER,
                GLenum inType = GL_FLOAT, GLenum inUsage = GL_STATIC_DRAW);
            virtual ~VertexBufferObject();

            inline void bind() const { glBindBuffer(mTarget, mHandle); }
            void loadData(const GLvoid* inData, GLuint inSize,
                GLuint inValuesPerUnit = 1);
            void editData(const GLvoid* inData, GLuint inFirst,
                GLuint inVertexCount = 1); // untested
            void enableVAA(GLuint inIndex);
            void disableVAA();

        protected:
            GLuint mHandle;
            GLuint mIndex;
            GLenum mTarget;
            GLenum mType;
            GLenum mUsage;
            GLuint mTypeSize;
            GLuint mValuesPerUnit;
            GLuint mSize;
    };
}

#endif
