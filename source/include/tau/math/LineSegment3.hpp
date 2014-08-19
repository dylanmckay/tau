#pragma once

#include "Vector3.hpp"

namespace tau
{
    namespace math
    {
        class LineSegment3
        {

        public:

            LineSegment3(const Vector3& point1, const Vector3& point2) : m_point1(point1), m_point2(point2)
            {

            }

            const Vector3& getPoint1() const
            {
                return m_point1;
            }

            const Vector3& getPoint2() const
            {
                return m_point2;
            }



        private:

            Vector3 m_point1;
            Vector3 m_point2;
        };
    }
}
