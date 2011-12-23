#ifndef WIDGET_H
#define WIDGET_H

#include "EventListener.h"
#include "../SceneGraphNode.h"
#include <cstring>

namespace CGE
{
    class Widget : public SceneGraphNode
    {
        public:
            Widget(bool inCanHaveFocus = true);
            virtual ~Widget();

            virtual void display() = 0;

            inline void enable(bool inEnabled = true)
            {
                mEnabled = inEnabled;
            }

            inline void disable()
            {
                mEnabled = false;
            }

            inline bool isEnabled()
            {
                return mEnabled;
            }

            inline bool isDisabled()
            {
                return !mEnabled;
            }

            inline bool canHaveFocus() const
            {
                return mEnabled && mCanHaveFocus;
            }

            inline bool contains(float inX, float inY) const
            {
                return inX >= mX - mRadiusX
                    && inX <= mX + mRadiusX
                    && inY >= mY - mRadiusY
                    && inY <= mY + mRadiusY;
            }

            virtual void onMouseIn(bool inIsClickCandidate);
            virtual void onMouseOut();
            virtual void onMouseDown();
            virtual void onMouseUp();
            virtual void onClick();
            virtual void onFocus();
            virtual void onBlur();

            void setMouseInListener(Listener inListener, void* inData = NULL);
            void setMouseOutListener(Listener inListener, void* inData = NULL);
            void setMouseDownListener(Listener inListener, void* inData = NULL);
            void setMouseUpListener(Listener inListener, void* inData = NULL);
            void setClickListener(Listener inListener, void* inData = NULL);
            void setFocusListener(Listener inListener, void* inData = NULL);
            void setBlurListener(Listener inListener, void* inData = NULL);

        protected:
            float mX;
            float mY;
            float mRadiusX;
            float mRadiusY;

        private:
            bool mEnabled;
            bool mCanHaveFocus;
            bool mVisible;
            EventListener mOnMouseIn;
            EventListener mOnMouseOut;
            EventListener mOnMouseDown;
            EventListener mOnMouseUp;
            EventListener mOnClick;
            EventListener mOnFocus;
            EventListener mOnBlur;
    };
}

#endif
