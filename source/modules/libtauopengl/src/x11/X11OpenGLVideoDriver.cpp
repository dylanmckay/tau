#include "../../include/x11/X11OpenGLVideoDriver.hpp"

#include "../../include/x11/X11OpenGLDevice.hpp"

#include<GL/gl.h>

using namespace tau;
using namespace tau::graphics;
using namespace tau::graphics::opengl;
using namespace tau::graphics::opengl::x11;

void X11OpenGLVideoDriver::beginScene(bool clearBackBuffer, bool clearZBuffer)
{
    clear(clearBackBuffer, clearZBuffer);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void X11OpenGLVideoDriver::endScene()
{
    glFinish();
    glXSwapBuffers(m_device->m_display, m_device->m_window);
}
