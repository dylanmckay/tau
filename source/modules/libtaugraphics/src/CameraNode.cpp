#include "../../../include/tau/graphics/CameraNode.hpp"

#include "../../../include/tau/graphics/SceneManager.hpp"
#include "../../../include/tau/graphics/TauDevice.hpp"
#include "../../../include/tau/graphics/VideoDriver.hpp"
#include "../../../include/tau/math/Quaternion.hpp"
#include "../../../include/tau/math/Matrix4.hpp"

using namespace tau;
using namespace tau::graphics;
using namespace tau::math;

CameraNode::CameraNode(SceneManager* smgr,
                       Node* parent,
                       const Vector3& position,
                       float moveSpeed) :
                                 Node(smgr, parent, position),

                                 m_direction(0,0,1),
                                 m_up(0,1,0),
                                 m_moveSpeed(moveSpeed)
{
    //setTarget(Vector3(0,0,0));
}

void CameraNode::moveForward(float units)
{
    m_position -= m_direction*m_moveSpeed*units;
}

void CameraNode::moveBackward(float units)
{
    m_position += m_direction*m_moveSpeed*units;
}

void CameraNode::moveLeft(float units)
{
    Vector3 strafeVec(m_up.crossProduct(m_direction));

    m_position -= strafeVec*m_moveSpeed*units;
}

void CameraNode::moveRight(float units)
{
    Vector3 strafeVec(m_up.crossProduct(m_direction));

    m_position += strafeVec*m_moveSpeed*units;
}

void CameraNode::rotateCamera(double angle, double x, double y, double z)
{
    Vector3 view(getTarget());

    Quaternion temp, quat_view, result;

    temp.setX(x * sine(angle/2));
    temp.setY(y * sine(angle/2));
    temp.setZ(z * sine(angle/2));
    temp.setW(cosine(angle/2));

    quat_view.setX(view.getX());
    quat_view.setY(view.getY());
    quat_view.setZ(view.getZ());
    quat_view.setW(0);

    result = (temp * quat_view) * temp.getConjugate();

    view = Vector3(result.getX(), result.getY(), result.getZ());
    setTarget(view);
}

void CameraNode::render()
{
    m_smgr->getVideoDriver()->setProjectionMatrix(buildProjectionMatrix());
    m_smgr->getVideoDriver()->setViewMatrix(buildCameraTransform());

    renderChildren();
}

math::Matrix4 CameraNode::buildProjectionMatrix() const
{
    TauDevice* device = m_smgr->getDevice();

    Scalar near = 1;
    Scalar far = 50;

    Scalar width = device->getSize().getWidth();
    Scalar height = device->getSize().getHeight();
    Scalar aspect = width/height;

    return Matrix4::BuildPerspectiveProjectionMatrix(-Pi/4, aspect, near, far);
}

Matrix4 CameraNode::buildCameraTransform() const
{
    return Matrix4::BuildCameraTransform(m_position, m_direction, m_up);
}
