#pragma once

#include <tau/graphics/TauDevice.hpp>

namespace tau
{
    namespace graphics
    {
        namespace opengl
        {
            class OpenGLDevice : public TauDevice
            {

            public:

                OpenGLDevice();

                virtual ~OpenGLDevice() { }

                SceneManager* getSceneManager() override;

            private:

                SceneManager* m_smgr;
            };
        }
    }
}
