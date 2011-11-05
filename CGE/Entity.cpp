#include "Entity.h"
#include "Control.h"

namespace CGE
{
    Entity::Entity() : mMass(1.0), mRadius(1.0), mMaxSpeed(0.0),
        mCurrentSpeed(0.0)
    {
    }

    Entity::~Entity()
    {
        for (size_t i = 0; i < mActors.size(); ++i)
        {
            mActors[i]->removeFromBin();
            delete mActors[i];
        }
    }

    void Entity::update()
    {
        mTransform.loadIdentity();

        mTransform.translate(float(mPosition[0]), float(mPosition[1]),
            float(mPosition[2]));


        mTransform.rotateY(mDefaultRotation[1]);
        mTransform.rotateX(mDefaultRotation[0]);
        mTransform.rotateZ(mDefaultRotation[2]);




    }
}
