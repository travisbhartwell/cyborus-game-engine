#ifndef ENTITY_H
#define ENTITY_H

#include "Actor.h"
#include "Vectors.h"
#include "LuaReference.h"
#include <lua.hpp>
#include <vector>

namespace CGE
{
    class Entity : public SceneGraphNode
    {
        public:
            Entity(lua_State* inState);
            virtual ~Entity();

            void update();
            void impact(const vec3d& inMomentum);
            bool isInRangeOf(Entity* inEntity);

            inline double getMass() const           { return mMass;         }
            inline double getRadius() const         { return mRadius;       }
            inline const vec3d& getPosition() const { return mPosition;     }
            inline const vec3d& getVelocity() const { return mVelocity;     }
            inline double getMaxSpeed() const       { return mMaxSpeed;     }
            inline double getCurrentSpeed() const   { return mCurrentSpeed; }

            inline void setMaxSpeed(double inSpeed) { mMaxSpeed = inSpeed;  }
            inline void setRadius(double inRadius)  { mRadius = inRadius;   }
            inline void setMass(double inMass)      { mMass = inMass;       }

            inline Actor* getActor(size_t inIndex)
            {
                return inIndex < mActors.size() ? mActors[inIndex] : NULL;
            }

            void setCollisionCB(lua_State* inState);

            void onCollision(lua_State* inState, Entity* inEntity);

            inline void setVelocity(const vec3d& inVelocity)
            {
                mVelocity = inVelocity;
            }

            inline void setVelocity(double inX, double inY, double inZ)
            {
                mVelocity[0] = inX;
                mVelocity[1] = inY;
                mVelocity[2] = inZ;
            }

            inline void rotateActor(int inActor, double inXRotation, double inYRotation, double inZRotation)
            {
                Actor* next = mActors[inActor];
                next->matrix().rotateX(inXRotation);
                next->matrix().rotateY(inYRotation);
                next->matrix().rotateZ(inZRotation);
            }

            inline void resetActorMatrix(int inActor)
            {
                mActors[inActor]->matrix().loadIdentity();
                //std::cerr << "actor: " << inActor << std::endl;
            }

            inline size_t numActors()
            {
                return mActors.size();
            }

            /*******************************************
            * Makes the entity turn at a percentage of
            * mMaxTurnSpeed on any of the axes
            *
            * Values passed in should be between -1.0 and 1.0, although
            * greater values can be used
            *******************************************/
            inline void setTurnRate(double inX, double inY, double inZ)
            {
                mTurn[0] = inX;
                mTurn[1] = inY;
                mTurn[2] = inZ;
            }

            /**********************************************
            * Sets the desired maximum rotation speed for each
            * axis.
            **********************************************/
            inline void setMaxTurnSpeed(double inX, double inY, double inZ)
            {
                mMaxTurnSpeed[0] = inX;
                mMaxTurnSpeed[1] = inY;
                mMaxTurnSpeed[2] = inZ;
            }

            inline const vec3d& getMomentum()
            {
                mMomentum[0] = mVelocity[0] * mMass;
                mMomentum[1] = mVelocity[1] * mMass;
                mMomentum[2] = mVelocity[2] * mMass;

                return mMomentum;
            }

            inline void setDefaultRotation(const vec3d& inDefault)
            {
                mDefaultRotation = inDefault;
            }

            inline void setCurrentSpeed(double inSpeed)
            {
                mCurrentSpeed = inSpeed;
            }

            inline void setPosition(const vec3d& inPosition)
            {
                mPosition = inPosition;
            }

            size_t addActor(Actor* inActor);
            size_t addActor(Actor* inActor, size_t inIndex);

        protected:
            vec3d mVelocity;
            vec3d mMomentum;
            vec3d mPosition;
            vec3d mRotation;
            vec3d mDefaultRotation;
            vec3d mMaxTurnSpeed;

            double mMass;
            double mRadius;
            double mMaxSpeed;
            double mCurrentSpeed;

            LuaReference mLuaTable;
            LuaReference mLuaCallback;

            // Value should be between -1.0 and 1.0, will cause the entity to
            // rotate a percentage of mMaxTurnSpeed.
            vec3d mTurn;

            std::vector<Actor*> mActors;
    };
}
#endif
