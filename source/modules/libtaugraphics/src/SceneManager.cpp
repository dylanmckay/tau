#include <tau/graphics/SceneManager.hpp>

#include <tau/graphics/TauDevice.hpp>
#include <tau/graphics/CameraNode.hpp>

using namespace tau;
using namespace tau::graphics;

SceneManager::SceneManager(TauDevice* device) : m_device(device),
                                                m_activeCamera(nullptr)
{

}

CameraNode* SceneManager::addCameraNode(Node* parent, const math::Vector3& position, float moveSpeed)
{
    CameraNode* node = new CameraNode(this, parent, position, moveSpeed);

    // Check if there is no active camera.
    if(!m_activeCamera)
        m_activeCamera = node; // activate this one.

    if(!parent)
        m_rootNodes.push_back(node);

    return node;
}

void SceneManager::renderAll()
{
    // don't render anything without a camera.
    if(!m_activeCamera)
        return;

    m_activeCamera->render();

    for(auto node : m_rootNodes)
    {
        if(node != m_activeCamera)
            node->render();
    }
}

VideoDriver* SceneManager::getVideoDriver()
{
    return m_device->getVideoDriver();
}
