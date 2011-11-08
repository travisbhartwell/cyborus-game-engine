#include "Entity.h"
#include "Control.h"
#include <cassert>

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
        mLuaTable.set(inState);
        mLuaCallback.set(inState);
    }

    void Entity::onCollision(lua_State* inState, Entity* inEntity)
    {
        assert(inState != NULL);
        assert(inEntity != NULL);

        if (mLuaCallback.isSet())
        {
            mLuaCallback.get();
            inEntity->mLuaTable.get();
            lua_call(inState, 1, 0);
        }
    }

    void Entity::setCollisionCB(lua_State* inState)
    {
        mLuaTable.set(inState);
        mLuaCallback.set(inState);
    }

    void Entity::onCollision(lua_State* inState, Entity* inEntity)
    {
        assert(inState != NULL);
        assert(inEntity != NULL);

        if (mLuaCallback.isSet())
        {
            mLuaCallback.get();
            inEntity->mLuaTable.get();
            lua_call(inState, 1, 0);
        }
    }
}
