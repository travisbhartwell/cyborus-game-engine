#include "Widget.h"

namespace CGE
{
    Widget::Widget(bool inCanHaveFocus) : mX(0.0f), mY(0.0f), mRadiusX(0.0f),
        mRadiusY(0.0f), mEnabled(true), mCanHaveFocus(inCanHaveFocus),
        mVisible(true)
    {
    }

    Widget::~Widget()
    {
    }

    void Widget::onMouseIn(bool inIsClickCandidate)
    {
        mOnMouseIn.dispatch(this);
    }

    void Widget::onMouseOut()
    {
        mOnMouseOut.dispatch(this);
    }

    void Widget::onMouseDown()
    {
        mOnMouseDown.dispatch(this);
    }

    void Widget::onMouseUp()
    {
        mOnMouseUp.dispatch(this);
    }

    void Widget::onClick()
    {
        mOnClick.dispatch(this);
    }

    void Widget::onFocus()
    {
        mOnFocus.dispatch(this);
    }

    void Widget::onBlur()
    {
        mOnBlur.dispatch(this);
    }

    void Widget::setMouseInListener(Listener inListener, void* inData)
    {
        mOnMouseIn.configure(inListener, inData);
    }

    void Widget::setMouseOutListener(Listener inListener, void* inData)
    {
        mOnMouseOut.configure(inListener, inData);
    }

    void Widget::setMouseDownListener(Listener inListener, void* inData)
    {
        mOnMouseDown.configure(inListener, inData);
    }

    void Widget::setMouseUpListener(Listener inListener, void* inData)
    {
        mOnMouseUp.configure(inListener, inData);
    }

    void Widget::setClickListener(Listener inListener, void* inData)
    {
        mOnClick.configure(inListener, inData);
    }

    void Widget::setFocusListener(Listener inListener, void* inData)
    {
        mOnFocus.configure(inListener, inData);
    }

    void Widget::setBlurListener(Listener inListener, void* inData)
    {
        mOnBlur.configure(inListener, inData);
    }
}
