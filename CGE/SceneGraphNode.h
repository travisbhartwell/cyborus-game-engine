#ifndef SCENEGRAPHNODE_H
#define SCENEGRAPHNODE_H

#include "Matrix4x4.h"

#include <list>

namespace CGE
{
    class SceneGraphNode
    {
        public:
            SceneGraphNode();
            virtual ~SceneGraphNode();

            virtual void display();

            void addChildNode(SceneGraphNode* inNode);
            void removeChildNode(SceneGraphNode* inNode);
            void removeAllChildren();
            void removeFromParentNode();

            void updateMatrices(const Matrix4x4<float>& inMatrix);

            inline const Matrix4x4<float>& compositeMatrix() const
            {
                return mCompositeTransform;
            }

        protected:
            Matrix4x4<float> mTransform;

        private:
            SceneGraphNode* mParent;
            std::list<SceneGraphNode*> mNodes;
            Matrix4x4<float> mCompositeTransform;
    };
}

#endif
