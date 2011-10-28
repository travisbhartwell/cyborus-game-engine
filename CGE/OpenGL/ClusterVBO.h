#ifndef CLUSTERVBO_H
#define CLUSTERVBO_H

#include "IndexVBO.h"

namespace CGE
{
    struct ClusterUnit
    {
        VertexBufferObject* buffer;
        GLuint index;
    };

    class ClusterVBO
    {
        public:
            ClusterVBO();
            ~ClusterVBO();

            void mount(const IndexVBO& inIVBO);
            void mount(VertexBufferObject& inVBO, GLuint inIndex);
            void display(GLenum inMode = GL_TRIANGLES);
            void display(const IndexVBO& inIVBO, GLenum inMode = GL_TRIANGLES);
            void display(GLenum inMode, GLint inFirst, GLsizei inCount);

        private:
            ClusterUnit mCluster[32];
            ClusterUnit* mTopCluster;
            const IndexVBO* mIVBO;
    };
}

#endif
