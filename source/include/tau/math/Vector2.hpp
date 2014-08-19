#pragma once

#include "Scalar.hpp"

namespace tau
{
    namespace math
    {
        /*!
         * Represents a 2 dimensional vector.
         * TODO: add +=, *=, etc. operators and add scalar addition, multipication, etc.
         */
        template<typename T>
        class BaseVector2
        {
        public:

            /*!
             * Creates a new, 2 dimensional null vector.
             */
            inline BaseVector2() : m_x(0), m_y(0)
            {

            }

            inline BaseVector2(T x, T y) : m_x(x), m_y(y)
            {

            }

            inline BaseVector2<T> operator+(const BaseVector2<T>& addend) const
            {
                return BaseVector2<T>(this->m_x + addend.m_x,
                                      this->m_y + addend.m_y);
            }

            inline BaseVector2<T> operator-(const BaseVector2<T>& minuend) const
            {
                return BaseVector2<T>(this->m_x - minuend.m_x,
                                      this->m_y - minuend.m_y);
            }

            inline BaseVector2<T> operator*(const BaseVector2<T>& multiplier) const
            {
                return BaseVector2<T>(this->m_x * multiplier.m_x,
                                      this->m_y * multiplier.m_y);
            }

            inline BaseVector2<T> operator/(const BaseVector2<T>& divisor) const
            {
                return BaseVector2<T>(this->m_x / divisor.m_x,
                                      this->m_y / divisor.m_y);
            }

            inline BaseVector2<T> operator*(Scalar s) const
            {
                return BaseVector2<T>(this->m_x * s,
                                      this->m_y * s);
            }

            void setX(T x)
            {
                m_x = x;
            }

            void setY(T y)
            {
                m_y = y;
            }

            inline T getX() const
            {
                return m_x;
            }

            inline T getY() const
            {
                return m_y;
            }


        private:

            T m_x;
            T m_y;
        };

        typedef BaseVector2<Scalar> Vector2;

        /*!
         * Represents a 2 dimensional vector of unsigned ints.
         */
        typedef BaseVector2<unsigned int> Vector2u;
    }
}
