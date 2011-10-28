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

#ifndef CONTROL_H
#define CONTROL_H

#include "Vectors.h"
#include "Entity.h"

namespace CGE
{
    class Control
    {
        protected:

        public:
            Control(Entity* inEntity);
            virtual ~Control();

            virtual void update() = 0;

            Entity* getEntity();

        protected:
            Entity* mEntity;

    };


    inline Entity* Control::getEntity()
    {
        return mEntity;
    }
}

#endif
