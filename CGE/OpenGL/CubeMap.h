#ifndef CUBEMAP_H
#define CUBEMAP_H

#include "Texture.h"
#include "../Image.h"

namespace CGE
{
    class CubeMap : public Texture
    {
        public:
            CubeMap();
            virtual ~CubeMap();

            void loadImages(const Image& inPositiveX, const Image& inNegativeX,
                const Image& inPositiveY, const Image& inNegativeY,
                const Image& inPositiveZ, const Image& inNegativeZ);

        private:
            CubeMap(const CubeMap& inCubeMap) : Texture(0)
            {
                // no copying
            }

            CubeMap& operator=(const CubeMap& inCubeMap)
            {
                // no copying
                return *this;
            }
    };
}

#endif
