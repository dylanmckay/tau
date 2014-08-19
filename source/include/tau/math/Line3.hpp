#pragma once

#include "Vector3.hpp"

namespace tau
{
    namespace math
    {
        /*!
         * Represents a line in 3D space that extends to infinity.
         */
        class Line3
        {

        public:

            Line3(const Vector3& position, const Vector3& direction) : m_position(position), m_direction(direction)
            {

            }

            /* 2D.
            bool isPointOnLine(const Vector3& point) const
            {
                Scalar a = -m_direction.getY();
                Scalar b = m_direction.getX();
                Scalar c = -(a*m_position.getX()) - (b * m_position.getY());

                Scalar result = (a * point.getX()) + (b * point.getY()) + c;

                return result == 0;
            }*/

            const Vector3& getPosition() const
            {
                return m_position;
            }

            const Vector3& getDirection() const
            {
                return m_direction;
            }


        private:

            Vector3 m_position;
            Vector3 m_direction;

        };
    }
}
