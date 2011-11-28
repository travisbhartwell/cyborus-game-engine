#ifndef CAMERA_H
#define CAMERA_H

#include "Matrix4x4.h"
#include "Vectors.h"

namespace CGE
{
    class Camera
    {
        public:
            Camera();
            ~Camera();

            inline const mat4f& getTranslateMatrix() const
            {
                return mTranslateMatrix;
            }

            inline const mat4f& getAngleMatrix() const
            {
                return mAngleMatrix;
            }

            void update();
            void setDistance(float inDistance);
            void changeDistance(float inOffset);
            void setRotation(float inRotation);
            void changeRotation(float inOffset);
            void setAngle(float inAngle);
            void changeAngle(float inOffset);
            void setPosition(float inX, float inY, float inZ);
            void changePosition(float inX, float inY, float inZ);
            void smartPan(float inX, float inY);

        private:
            mat4f mTranslateMatrix;
            mat4f mAngleMatrix;
            vec3f mPosition;
            float mDistance;
            float mRotation;
            float mAngle;
    };
}

#endif
