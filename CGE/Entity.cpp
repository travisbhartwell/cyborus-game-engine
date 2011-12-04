#include "Entity.h"
#include "Control.h"
#include <cassert>

namespace CGE
{
    Entity::Entity(lua_State* inState) : mMass(1.0), mRadius(1.0), mMaxSpeed(0.0),
        mCurrentSpeed(0.0)
    {
        assert(inState != NULL);
        mLuaTable.set(inState);
        mIsBeingDeleted = false;
    }

    Entity::~Entity()
    {
        for (size_t i = 0; i < mActors.size(); ++i)
        {
            Actor* a = mActors[i];
            delete a;
        }
    }

    bool Entity::isInRangeOf(Entity* inEntity)
    {
        if (!inEntity) return false;

        double squareTotal = 0.0;
        for (size_t i = 0; i < 3; ++i)
        {
            double d = mPosition[i] - inEntity->mPosition[i];
            squareTotal += d * d;
        }

        double radiusTotal = mRadius + inEntity->mRadius;
        double distance = sqrt(squareTotal);

        return distance < radiusTotal;
    }

    void Entity::update()
    {
        mPosition[0] += mVelocity[0];
        mPosition[1] += mVelocity[1];
        mPosition[2] += mVelocity[2];

        calculateForwardDirection();
        mActors[1]->resetMatrix();
        mActors[1]->translate(mForwardDirection[0], mForwardDirection[1], mForwardDirection[2]);


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

    void Entity::setCollisionCB(lua_State* inState)
    {
        assert(inState != NULL);
        mLuaCallback.set(inState);
    }

    void Entity::onCollision(lua_State* inState, Entity* inEntity)
    {
        assert(inState != NULL);
        assert(inEntity != NULL);

        if (mLuaCallback.isSet() && inEntity->mLuaTable.isSet())
        {
            mLuaCallback.get();
            inEntity->mLuaTable.get();
            lua_call(inState, 1, 0);
        }
    }

    size_t Entity::addActor(Actor* inActor)
    {
        assert(inActor != NULL);
        mActors.push_back(inActor);
        addChildNode(inActor);
        return mActors.size() - 1;
    }

    size_t Entity::addActor(Actor* inActor, size_t inIndex)
    {
        assert(inActor != NULL);
        mActors.push_back(inActor);

        if (inIndex < mActors.size())
            mActors[inIndex]->addChildNode(inActor);
        else
            addChildNode(inActor);

        return mActors.size() - 1;
    }

    void Entity::rotateActor(size_t inIndex, double inXRotation,
        double inYRotation, double inZRotation)
    {
        Actor* a = getActor(inIndex);
        if (a)
        {
            //a->matrix().rotateX(inXRotation);
            //a->matrix().rotateY(inYRotation);
            //a->matrix().rotateZ(inZRotation);
            a->rotateY(inYRotation);
            a->rotateX(inXRotation);
            a->rotateZ(inZRotation);
        }
    }
}
