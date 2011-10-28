/**
 *  This file is part of "Paroxysm".
 *
 *  "Paroxysm" is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  "Paroxysm" is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with "Paroxysm".  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ENTITY_H
#define ENTITY_H

#include "Vectors.h"

namespace CGE
{
    class Entity
    {
        public:
            Entity();
            virtual ~Entity();

            virtual void update();
            virtual void move() = 0;
            virtual void changeDirection(float inDirection) = 0;
            virtual void changeSpeed(float inSpeed) = 0;

            void setRadius(float inRadius);
            float getRadius();

            void addReference();
            Entity* getReference();
            void removeReference();
            bool hasReferences();

            const vec4f& getMomentum() const;
            const vec4f& getPosition() const;
            inline float getMaxSpeed() { return mMaxSpeed; }
            inline float getCurrentSpeed() { return mCurrentSpeed; }
            inline void setMaxSpeed(float inSpeed) { mMaxSpeed = inSpeed; }
            inline void setCurrentSpeed(float inSpeed) { mCurrentSpeed = inSpeed; }
            void setPosition(const vec4f& inPosition);

            bool isAlive();
            void die();

        protected:
            float mRadius;

            unsigned char mNumReferences;


            vec4f mMomentum;
            vec4f mPosition;
            vec4f mRotation;
            float mMaxSpeed;
            float mCurrentSpeed;

            bool mAlive;

    };

    inline void Entity::die()
    {
        mAlive = false;
    }

    inline const vec4f& Entity::getPosition() const
    {
        return mPosition;
    }

    inline const vec4f& Entity::getMomentum() const
    {
        return mMomentum;
    }

    inline float Entity::getRadius()
    {
        return mRadius;
    }

    inline bool Entity::isAlive()
    {
        return mAlive;
    }


    /***********************************
    *   Here for readability with a model that
    *   wasn't really built for reference counting.
    *   Just indicates that you are holding a reference
    *   to this entity somewhere
    *************************************/
    inline void Entity::addReference()
    {
        ++mNumReferences;
    }

    /**
    *   Adds to the number of references held to this entity
    *   and returns a reference to this entity.
    **/
    inline Entity* Entity::getReference()
    {
        ++mNumReferences;
        return this;
    }

    /**
    *   Removes a reference to this entity.
    **/
    inline void Entity::removeReference()
    {
        --mNumReferences;
    }

    /**
    *   Checks to see if there are any references being held to this entity
    **/
    inline bool Entity::hasReferences()
    {
        return mNumReferences > 0;
    }
}
#endif
