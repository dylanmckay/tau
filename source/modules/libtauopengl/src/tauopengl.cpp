#include <tau/graphics/TauDevice.hpp>
#include "../include/x11/X11OpenGLDevice.hpp"

using namespace tau;
using namespace tau::graphics;
using namespace tau::graphics::opengl;


TauDevice* TauDevice::Create()
{
    return new x11::X11OpenGLDevice();
}
