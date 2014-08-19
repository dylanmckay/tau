#include "../../include/x11/X11Mouse.hpp"

#include "../../include/x11/X11OpenGLDevice.hpp"

#include <tau/graphics/input/MouseMoveEvent.hpp>

using namespace tau;
using namespace tau::graphics;
using namespace tau::graphics::opengl;
using namespace tau::graphics::opengl::x11;

const math::Position2& X11Mouse::getPosition() const
{
    return m_position;
}

void X11Mouse::setPosition(const math::Position2& pos)
{
    m_position = pos;

    math::Position2u physicalPos = m_device->convertPosition2ToPixel(pos);
    XWarpPointer(m_device->getXDisplay(), None, m_device->getXWindow(), 0, 0, 0, 0, physicalPos.getX(), physicalPos.getY());
    m_ignoreNextMove = true;
}

void X11Mouse::handleX11MouseEvent(XEvent xev)
{
    switch(xev.type)
    {
        case MotionNotify:
        {
            if(m_ignoreNextMove)
            {
                m_ignoreNextMove = false;
                return;
            }

            const math::Position2 oldPos = m_position;

            XMotionEvent realEvt = xev.xmotion;

            int curX = realEvt.x;
            int curY = realEvt.y;

            m_position = m_device->convertPixelToPosition2(math::Position2u(curX, curY));

            // Create the event and dispatch it.
            input::MouseMoveEvent event(oldPos, m_position);
            m_device->dispatchEvent(event);
        }
    }
}
