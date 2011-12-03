#include "SceneGraphNode.h"
#include <cassert>

namespace CGE
{
    SceneGraphNode::SceneGraphNode() : mParent(NULL)
    {
    }

    SceneGraphNode::~SceneGraphNode()
    {
        removeFromParentNode();
        removeAllChildren();
    }

    void SceneGraphNode::display()
    {
    }

    void SceneGraphNode::addChildNode(SceneGraphNode* inNode)
    {
        assert(inNode != NULL);
        inNode->removeFromParentNode();
        inNode->mParent = this;
        mNodes.push_back(inNode);
    }

    void SceneGraphNode::removeChildNode(SceneGraphNode* inNode)
    {
        assert(inNode != NULL);
        inNode->mParent = NULL;
        mNodes.remove(inNode);
    }

    void SceneGraphNode::removeAllChildren()
    {
        for (std::list<SceneGraphNode*>::iterator i = mNodes.begin();
            i != mNodes.end(); ++i)
        {
            SceneGraphNode& sgn = *(*i);
            sgn.mParent = NULL;
        }

        mNodes.clear();
    }

    void SceneGraphNode::removeFromParentNode()
    {
        if (mParent) mParent->removeChildNode(this);
    }

    void SceneGraphNode::updateMatrices(const CGE::Matrix4x4<float>& inMatrix)
    {
        mCompositeTransform.multiply(inMatrix, mTransform);
        for (std::list<SceneGraphNode*>::iterator i = mNodes.begin();
            i != mNodes.end(); ++i)
        {
            SceneGraphNode& sgn = *(*i);
            sgn.updateMatrices(mCompositeTransform);
        }
    }
}
