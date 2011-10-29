#ifndef ACTOR_H
#define ACTOR_H

#include "SceneGraphNode.h"
#include "Matrix4x4.h"
#include "Model.h"

namespace CGE
{
    class Actor : public SceneGraphNode
    {
        public:
            friend class RenderBin;

            Actor(Model* inModel);
            virtual ~Actor();

            inline void display() { mModel->display(); }
            inline CGE::Matrix4x4<float>& matrix() { return mTransform; }

            void removeFromBin();

        private:
            Model* mModel;

            Actor** mHead;
            Actor* mNextActor;
            Actor* mPreviousActor;
    };
}
#endif
