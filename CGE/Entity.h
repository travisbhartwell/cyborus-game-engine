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
            virtual void changeDirection(double inDirection) = 0;
            virtual void changeSpeed(double inSpeed) = 0;

            inline double getMass() const           { return mMass;         }
            inline double getRadius() const         { return mRadius;       }
            inline const vec4d& getMomentum() const { return mMomentum;     }
            inline const vec4d& getPosition() const { return mPosition;     }
            inline double getMaxSpeed() const       { return mMaxSpeed;     }
            inline double getCurrentSpeed() const   { return mCurrentSpeed; }

            inline void setMaxSpeed(double inSpeed) { mMaxSpeed = inSpeed;  }
            inline void setRadius(double inRadius)  { mRadius = inRadius;   }

            inline void setCurrentSpeed(double inSpeed)
            {
                mCurrentSpeed = inSpeed;
            }

            inline void setPosition(const vec4d& inPosition)
            {
                mPosition = inPosition;
            }

        protected:
            vec4d mMomentum;
            vec4d mPosition;
            vec4d mRotation;

            double mMass;
            double mRadius;
            double mMaxSpeed;
            double mCurrentSpeed;
    };
}
#endif
