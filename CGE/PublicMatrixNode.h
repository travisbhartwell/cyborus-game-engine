#ifndef PUBLICMATRIXNODE_H
#define PUBLICMATRIXNODE_H

#include "SceneGraphNode.h"

namespace CGE
{
    class PublicMatrixNode : public SceneGraphNode
    {
        public:
            PublicMatrixNode();
            virtual ~PublicMatrixNode();

            inline mat4f& matrix() { return mTransform; }

        protected:
        private:
    };
}

#endif
