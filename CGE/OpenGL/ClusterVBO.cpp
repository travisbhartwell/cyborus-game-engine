#include "ClusterVBO.h"

namespace CGE
{
    ClusterVBO::ClusterVBO() : mTopCluster(mCluster), mIVBO(NULL)
    {
        memset(mCluster, 0, sizeof(mCluster));
    }

    ClusterVBO::~ClusterVBO()
    {
    }

    void ClusterVBO::mount(const IndexVBO& inIVBO)
    {
        mIVBO = &inIVBO;
    }

    void ClusterVBO::mount(VertexBufferObject& inVBO, GLuint inIndex)
    {
        mTopCluster->buffer = &inVBO;
        mTopCluster->index = inIndex;
        ++mTopCluster;
    }

    void ClusterVBO::display(GLenum inMode)
    {
        display(*mIVBO, inMode);
    }

    void ClusterVBO::display(const IndexVBO& inIVBO, GLenum inMode)
    {
        for (ClusterUnit* i = mCluster; i->buffer; ++i)
            i->buffer->enableVAA(i->index);

        inIVBO.draw(inMode);

        for (ClusterUnit* i = mCluster; i->buffer; ++i)
            i->buffer->disableVAA();
    }

    void ClusterVBO::display(GLenum inMode, GLint inFirst, GLsizei inCount)
    {
        for (ClusterUnit* i = mCluster; i->buffer; ++i)
            i->buffer->enableVAA(i->index);

        glDrawArrays(inMode, inFirst, inCount);

        for (ClusterUnit* i = mCluster; i->buffer; ++i)
            i->buffer->disableVAA();
    }
}
