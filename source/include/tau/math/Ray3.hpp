#pragma once

namespace tau
{
    namespace math
    {
        class Ray3
        {

        public:

            Ray3(const Vector3& position, const Vector3& direction) : m_position(position), m_direction(direction)
            {

            }

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
