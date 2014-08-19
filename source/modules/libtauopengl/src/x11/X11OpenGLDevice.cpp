#include "../../include/x11/X11OpenGLDevice.hpp"

#include <tau/graphics/input/Key.hpp>
#include <tau/graphics/input/KeyboardEvent.hpp>
#include <tau/TauException.hpp>

#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>

using namespace tau;
using namespace tau::graphics;
using namespace tau::graphics::input;
using namespace tau::graphics::opengl;
using namespace tau::graphics::opengl::x11;



namespace
{
    // TODO: this can't be constant, context creation may change it.
    GLint GLAttributes[] = {GLX_RGBA, GLX_DEPTH_SIZE, 24};

    const long X11EventMask = KeyPressMask | PointerMotionMask | StructureNotifyMask;

    /*!
     * Converts an X11 keycode value to an enum.
     */
    graphics::input::Key XLibKeycodeToEnum(unsigned int keycode)
    {
        switch(keycode)
        {
            case 111:
                return Key::Up;
            case 113:
                return Key::Left;
            case 114:
                return Key::Right;
            case 116:
                return Key::Down;
            default:
                return Key::Unknown;
        }
    }
}




X11OpenGLDevice::X11OpenGLDevice()
{
    m_driver = new X11OpenGLVideoDriver(this);
    m_mouse = new X11Mouse(this);

    createX11Window();
}

X11OpenGLDevice::~X11OpenGLDevice()
{
    glXMakeCurrent(m_display, None, nullptr);
    glXDestroyContext(m_display, m_glContext);
    XDestroyWindow(m_display, m_window);
    XCloseDisplay(m_display);
}

void X11OpenGLDevice::createX11Window()
{
    m_size = math::Dimension2u(1024, 768);

    ::Window rootWindow;
    XSetWindowAttributes setWinAttrs;

    m_display = XOpenDisplay(nullptr);

    if(!m_display)
        throw TauException("could not open X11 display");


    rootWindow = DefaultRootWindow(m_display);

    m_visualInfo = glXChooseVisual(m_display, 0, GLAttributes);

    if(!m_visualInfo)
        throw TauException("no appropriate visual found");

    ::Colormap m_colorMap = XCreateColormap(m_display, rootWindow, m_visualInfo->visual, AllocNone);

    setWinAttrs.colormap = m_colorMap;
    setWinAttrs.event_mask = X11EventMask;

    m_window = XCreateWindow(m_display, rootWindow, 0, 0, m_size.getWidth(), m_size.getHeight(), 0, m_visualInfo->depth, InputOutput, m_visualInfo->visual, CWColormap|CWEventMask, &setWinAttrs);

    m_deleteMessage = XInternAtom(m_display, "WM_DELETE_WINDOW", False);
    XSetWMProtocols(m_display, m_window, &m_deleteMessage, 1);

    // Show the window.
    XMapWindow(m_display, m_window);

    // Set the title.
    XStoreName(m_display, m_window, "Tau Engine");

    // Create the OpenGL context.
    m_glContext = glXCreateContext(m_display, m_visualInfo, nullptr, GL_TRUE);

    // Set the current context.
    glXMakeCurrent(m_display, m_window, m_glContext);

    // Enable depth testing.
    glEnable(GL_DEPTH_TEST);

    m_running = true;
}

void X11OpenGLDevice::run()
{
    if(XPending(m_display) == 0)
        return;

    XEvent event;
    XNextEvent(m_display, &event);

    switch(event.type)
    {
        case MotionNotify:
        {
            m_mouse->handleX11MouseEvent(event);

            break;
        }
        case ConfigureNotify:
        {
            math::Dimension2u curSize(event.xconfigure.width, event.xconfigure.height);

            // The event was a size changed event.
            if(m_size != curSize)
            {
                m_size = curSize;

                glViewport(0, 0, event.xconfigure.width, event.xconfigure.height);

                // notify?.
            }

            break;
        }
        case KeyPress:
        {
            Key key = XLibKeycodeToEnum(event.xkey.keycode);

            KeyboardEvent event(key);

            dispatchEvent(event);

            break;
        }
        case KeyRelease:
        {
            Key key = XLibKeycodeToEnum(event.xkey.keycode);

            KeyboardEvent event(key, true);

            dispatchEvent(event);

            break;
        }
        case ClientMessage:
        {
            // Handle a close event.
            if(event.xclient.data.l[0] == (int)m_deleteMessage)
            {
                m_running = false;
                glXDestroyContext(m_display, m_glContext);
                //XDestroyWindow(m_display, m_window);
            }

            break;
        }
    }
}

bool X11OpenGLDevice::isRunning() const
{
    return m_running;
}

const math::Dimension2u& X11OpenGLDevice::getSize() const
{
    return m_size;
}

X11OpenGLVideoDriver* X11OpenGLDevice::getVideoDriver()
{
    return m_driver;
}

X11Mouse* X11OpenGLDevice::getMouse()
{
    return m_mouse;
}
