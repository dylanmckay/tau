#pragma once

#include "Node.hpp"

#include "../math/Scalar.hpp"
#include "../math/Vector3.hpp"
#include "../math/forward.hpp"
#include "forward.hpp"

namespace tau
{
    namespace graphics
    {
        class CameraNode : public Node
        {

        public:

            CameraNode(SceneManager* smgr, Node* parent, const math::Vector3& position, float moveSpeed = 100);

            void moveForward(float units);

            void moveBackward(float units);

            void moveLeft(float units);

            void moveRight(float units);

            void rotateCamera(double angle, double x, double y, double z);

            void render() override;

            inline void setDirection(const math::Vector3& direction)
            {
                m_direction = direction;
            }

            const math::Vector3& getDirection() const
            {
                return m_direction;
            }

            inline void setTarget(const math::Vector3& target)
            {
                m_direction = target - m_position;
            }

            math::Vector3 getTarget() const
            {
                return m_position + m_direction;
            }

            inline const math::Vector3& getUpVector() const
            {
                return m_up;
            }

            math::Matrix4 buildProjectionMatrix() const;

            math::Matrix4 buildCameraTransform() const;



        private:

            math::Vector3 m_direction;
            math::Vector3 m_up;

            float m_moveSpeed;
        };
    }
}
