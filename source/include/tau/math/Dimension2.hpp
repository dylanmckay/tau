#pragma once

#include "Scalar.hpp"

namespace tau
{
    namespace math
    {
        template<typename T>
        class BaseDimension2
        {

        public:

            inline BaseDimension2() : m_x(0), m_y(0)
            {

            }

            inline BaseDimension2(T x, T y) : m_x(x), m_y(y)
            {

            }

            inline bool operator==(const BaseDimension2<T>& cmp) const
            {
                return (this->m_x == cmp.m_x) && (this->m_y == cmp.m_y);
            }

            inline bool operator!=(const BaseDimension2<T>& cmp) const
            {
                return (this->m_x != cmp.m_x) || (this->m_y != cmp.m_y);
            }

            T getWidth() const
            {
                return m_x;
            }

            T getHeight() const
            {
                return m_y;
            }


        private:

            T m_x;
            T m_y;
        };

        typedef BaseDimension2<Scalar> Dimension2;

        typedef BaseDimension2<unsigned int> Dimension2u;
    }
}
