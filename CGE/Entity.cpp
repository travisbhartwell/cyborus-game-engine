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
        mPosition[0] += mVelocity[0];
        mPosition[1] += mVelocity[1];
        mPosition[2] += mVelocity[2];

        mTransform.loadIdentity();

        mTransform.translate(float(mPosition[0]), float(mPosition[1]),
            float(mPosition[2]));

        mTransform.rotateY(mDefaultRotation[1]);
        mTransform.rotateX(mDefaultRotation[0]);
        mTransform.rotateZ(mDefaultRotation[2]);

    }

    void Entity::impact(const vec3d& inMomentum)
    {

        const vec3d& vec = getMomentum();
        mVelocity[0] = (vec[0] + inMomentum[0]) / getMass();
        mVelocity[1] = (vec[1] + inMomentum[1]) / getMass();
        mVelocity[2] = (vec[2] + inMomentum[2]) / getMass();

    }


}
