#pragma once

#include <tau/graphics/input/Mouse.hpp>
#include <tau/math/Position2.hpp>

#include "forward.hpp"

#include <X11/Xlib.h>

namespace tau
{
    namespace graphics
    {
        namespace opengl
        {
            namespace x11
            {
                class X11Mouse : public input::Mouse
                {

                public:

                    X11Mouse(X11OpenGLDevice* device) : m_device(device),
                                                        m_ignoreNextMove(false)
                    {

                    }

                    const math::Position2& getPosition() const override;

                    void setPosition(const math::Position2& pos) override;

                    void handleX11MouseEvent(XEvent xev);

                private:

                    X11OpenGLDevice* m_device;

                    math::Position2 m_position;

                    bool m_ignoreNextMove;
                };
            }
        }
    }
}
