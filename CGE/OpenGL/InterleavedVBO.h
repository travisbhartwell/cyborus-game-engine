#ifndef INTERLEAVEDVBO_H
#define INTERLEAVEDVBO_H

#include "IndexVBO.h"

namespace CGE
{
    class InterleavedVBO
    {
        public:
            InterleavedVBO();
            virtual ~InterleavedVBO();

            inline void bind() const
            {
                glBindBuffer(GL_ARRAY_BUFFER, mHandle);
            }

            inline GLuint vertexSize() const
            {
                return mVertexSize;
            }

            void addField(GLuint inIndex, GLuint inSize = 1);
            void loadData(GLvoid* inData, GLuint inSize);
            void enableVAA();
            void disableVAA();

            void display(const IndexVBO& inIVBO, GLenum inMode = GL_TRIANGLES);
            void display(GLenum inMode, GLint inFirst, GLsizei inCount);

        protected:
            static inline GLvoid* bufferOffset(size_t inOffset)
            {
                return ((char*)0) + inOffset;
            }

        private:
            static const size_t MaxMappings = 16;

            struct FieldMapping
            {
                GLuint index;
                GLuint size;
            };

            GLuint mHandle;
            GLuint mVertexSize;
            GLuint mNumVertices;
            FieldMapping mMappings[MaxMappings];
            size_t mNumMappings;
    };
}

#endif
