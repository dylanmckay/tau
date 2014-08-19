#pragma once

#include "../OpenGLVideoDriver.hpp"

#include "forward.hpp"

namespace tau
{
    namespace graphics
    {
        namespace opengl
        {
            namespace x11
            {
                class X11OpenGLVideoDriver : public OpenGLVideoDriver
                {

                public:

                    void beginScene(bool clearBackBuffer = true, bool clearZBuffer = true) override;

                    void endScene() override;

                private:

                    inline X11OpenGLVideoDriver(X11OpenGLDevice* device) : m_device(device) { }

                    X11OpenGLDevice* m_device;

                    friend class X11OpenGLDevice;
                };
            }
        }
    }
}
