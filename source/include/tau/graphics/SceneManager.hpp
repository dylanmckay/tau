#pragma once

#include "../ReferenceCounted.hpp"

#include "forward.hpp"
#include "../math/Vector3.hpp"

#include <vector>

namespace tau
{
    namespace graphics
    {
        class SceneManager : public ReferenceCounted
        {

        public:

            SceneManager(TauDevice* device);

            CameraNode* addCameraNode(Node* parent = nullptr,
                                         const math::Vector3& position = math::Vector3(0,0,0),
                                         float moveSpeed = 100);

            void renderAll();

            /*!
             * Sets the active camera.
             */
            void setActiveCamera(CameraNode* camera)
            {
                m_activeCamera = camera;
            }

            /*!
             * Gets the active camera, or null if no camera is active.
             */
            CameraNode* getActiveCamera()
            {
                return m_activeCamera;
            }

            inline TauDevice* getDevice()
            {
                return m_device;
            }

            VideoDriver* getVideoDriver();

        private:

            TauDevice* m_device;

            CameraNode* m_activeCamera;

            std::vector<Node*> m_rootNodes;
        };
    }
}
