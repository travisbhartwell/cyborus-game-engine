#include "Camera.h"
#include "Tools.h"

namespace CGE
{
    Camera::Camera() : mDistance(0.0f), mRotation(0.0f), mAngle(0.0f),
        mFollow(NULL)
    {
    }

    Camera::~Camera()
    {
    }

    void Camera::update()
    {
        mAngleMatrix.loadIdentity();
        if (mDistance > 0.0f) mAngleMatrix.translate(0.0f, 0.0f, -mDistance);
        mAngleMatrix.rotateX(mAngle);
        mAngleMatrix.rotateZ(mRotation);

        mTranslateMatrix.loadIdentity();

        if (mFollow)
        {
            const vec3d& position = mFollow->getPosition();

            mTranslateMatrix.translate(-position[0], -position[1],
                -position[2]);
        }
        else
        {
            mTranslateMatrix.translate(-mPosition[0], -mPosition[1],
                -mPosition[2]);
        }

    }

    void Camera::setDistance(float inDistance)
    {
        if (inDistance < 0.0f)
            mDistance = 0.0f;
        else
            mDistance = inDistance;
    }

    void Camera::changeDistance(float inOffset)
    {
        setDistance(mDistance + inOffset);
    }

    void Camera::setRotation(float inRotation)
    {
        if (inRotation < 0.0f)
            mRotation = fmod(inRotation - 180.0f, 360.0f) + 180.0f;
        else
            mRotation = fmod(inRotation + 180.0f, 360.0f) - 180.0f;
    }

    void Camera::changeRotation(float inOffset)
    {
        setRotation(mRotation + inOffset);
    }

    void Camera::setAngle(float inAngle)
    {
        if (inAngle < 0.0f)
            mAngle = fmod(inAngle - 180.0f, 360.0f) + 180.0f;
        else
            mAngle = fmod(inAngle + 180.0f, 360.0f) - 180.0f;
    }

    void Camera::changeAngle(float inOffset)
    {
        setAngle(mAngle + inOffset);
    }

    void Camera::setPosition(float inX, float inY, float inZ)
    {
        mPosition[0] = inX;
        mPosition[1] = inY;
        mPosition[2] = inZ;
    }

    void Camera::changePosition(float inX, float inY, float inZ)
    {
        mPosition[0] = inX;
        mPosition[1] = inY;
        mPosition[2] = inZ;
    }

    void Camera::smartPan(float inX, float inY)
    {
         float theta = TO_RADIANS(mRotation);
         float c = cos(theta);
         float s = sin(theta);

         float dxp = c * inX;
         float dyp = -s * inX;
         dxp += s * inY;
         dyp += c * inY;

         mPosition[0] += dxp;
         mPosition[1] += dyp;
    }

    void Camera::unfollow(bool inCopyEntityPosition)
    {
        if (mFollow && inCopyEntityPosition)
        {
            const vec3d& position = mFollow->getPosition();
            mPosition[0] = float(position[0]);
            mPosition[1] = float(position[1]);
            mPosition[2] = float(position[2]);
        }

        mFollow = NULL;
    }

    void Camera::unfollow(Entity* inEntity, bool inCopyEntityPosition)
    {
        if (mFollow == inEntity) unfollow(inEntity, inCopyEntityPosition);
    }
}
