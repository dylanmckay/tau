#pragma once

#include "../OpenGLDevice.hpp"

#include "X11OpenGLVideoDriver.hpp"
#include "X11Mouse.hpp"

#include <X11/X.h>
#include <X11/Xlib.h>
#include <GL/glx.h>

namespace tau
{
    namespace graphics
    {
        namespace opengl
        {
            namespace x11
            {
                class X11OpenGLDevice : public OpenGLDevice
                {

                public:

                    X11OpenGLDevice();

                    ~X11OpenGLDevice();

                    void createX11Window();

                    void run() override;

                    bool isRunning() const override;

                    const math::Dimension2u& getSize() const override;

                    X11OpenGLVideoDriver* getVideoDriver() override;

                    X11Mouse* getMouse() override;

                    inline Display* getXDisplay() { return m_display; }

                    inline Window getXWindow() { return m_window; }

                    inline XVisualInfo* getXVisualInfo() { return m_visualInfo; }

                    inline GLXContext getXGLContext() { return m_glContext; }



                private:

                    ::Display*     m_display;
                    //::Window       m_rootWindow;
                    ::Window       m_window;
                    ::XVisualInfo* m_visualInfo;
                    ::GLXContext   m_glContext;
                    ::Atom         m_deleteMessage;

                    // Whether the device is still running.
                    bool m_running;

                    // The video driver.
                    X11OpenGLVideoDriver* m_driver;

                    X11Mouse* m_mouse;

                    math::Dimension2u m_size;


                    friend class X11OpenGLVideoDriver;
            };
            }

        }
    }
}
