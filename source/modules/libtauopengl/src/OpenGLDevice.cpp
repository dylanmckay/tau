#include "../include/OpenGLDevice.hpp"

#include <tau/graphics/SceneManager.hpp>

using namespace tau;
using namespace graphics;
using namespace opengl;

OpenGLDevice::OpenGLDevice()
{
    m_smgr = new SceneManager(this);
}

SceneManager* OpenGLDevice::getSceneManager()
{
    return m_smgr;
}
