#ifndef ACTOR_H
#define ACTOR_H

#include "SceneGraphNode.h"
#include "Matrix4x4.h"
#include "Model.h"
#include "Vectors.h"

namespace CGE
{
    class Actor : public SceneGraphNode
    {
        public:
            friend class RenderBin;

            Actor(Model* inModel);
            virtual ~Actor();

            inline void display() { mModel->display(); }
            //inline CGE::Matrix4x4<float>& matrix() { return mTransform; }

            inline void resetMatrix()
            {
                mTransform.loadIdentity();
                mRotation[0] = 0;
                mRotation[1] = 0;
                mRotation[2] = 0;

                mTranslation[0] = 0;
                mTranslation[1] = 0;
                mTranslation[2] = 0;

                mScale[0] = 0;
                mScale[1] = 0;
                mScale[2] = 0;
            }

            inline void translate(double inX, double inY, double inZ)
            {
                mTransform.translate(inX, inY, inZ);
                mTranslation[0] += inX;
                mTranslation[1] += inY;
                mTranslation[2] += inZ;
            }

            inline vec3d& getTranslation()
            {
                return mTranslation;
            }

            inline void scale(double inX, double inY, double inZ)
            {
                mTransform.scale(inX, inY, inZ);

                mScale[0] += inX;
                mScale[1] += inY;
                mScale[2] += inZ;
            }

            inline void scale(double inScale)
            {
                mTransform.scale(inScale);

                mScale[0] += inScale;
                mScale[1] += inScale;
                mScale[2] += inScale;
            }

            inline vec3d& getScale()
            {
                return mScale;
            }

            inline void rotateX(double inX)
            {
                mTransform.rotateX(inX);
                mRotation[0] += inX;
            }

            inline void rotateY(double inY)
            {
                mTransform.rotateY(inY);
                mRotation[1] += inY;
            }

            inline void rotateZ(double inZ)
            {
                mTransform.rotateZ(inZ);
                mRotation[2] += inZ;
            }

            inline vec3d getRotation()
            {
                return mRotation;
            }

            void removeFromBin();

        private:
            Model* mModel;

            vec3d mRotation;
            vec3d mTranslation;
            vec3d mScale;

            Actor** mHead;
            Actor* mNextActor;
            Actor* mPreviousActor;
    };
}
#endif
